/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_formatted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:56:17 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 16:50:44 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *Raytracer interactif en un seul fichier C avec lecture d'un fichier de configuration (.rt)
 *
 *Compilation (exemple sous Linux) :
 *  gcc raytracer.c -lSDL2 -lm -O2 -o raytracer
 *
 *Utilisation :
 *  ./raytracer config.rt
 *Si aucun fichier n'est passé en argument, une scène par défaut est utilisée.
 */


// Ambient et caméra (JE GARDE POUR FAIRE LA FONCTION UN EXEMPLE)

float					ambient_ratio = 0.1f;
t_vec3					ambient_color = {0.1f, 0.1f, 0.1f};
t_vec3					camPos = {0.0f, 0.0f, 0.0f};
t_vec3					camDir = {0.0f, 0.0f, -1.0f};
float					fov = 90.0f;
float					yaw = 0.0f;// vue de gauche a droite
float					pitch = 0.0f; // vue de haut en bas en radians

// ----- Parsing du fichier de configuration -----
void	load_config(const char *filename)
{
//----	Jlaisse pour contextualiser -----
	while (fgets(line, sizeof(line), fp))
	{
		// Ignore les lignes vides ou commençant par #
		if (line[0] == '\n' || line[0] == '#')
			continue ;
		// Ambient lighting: A ratio R,G,B
		if (line[0] == 'A')
		{
			int r, g, b;
			if (sscanf(line, "A %f %d,%d,%d", &ratio, &r, &g, &b) == 4)
			{
				ambient_ratio = ratio;
				ambient_color = (t_vec3){r / 255.0f, g / 255.0f, b / 255.0f};
				printf("Ambiance : ratio=%.2f, color=(%d,%d,%d)\n", ratio, r, g,
					b);
			}
		}
		// Camera: C pos_x,pos_y,pos_z norm_x,norm_y,norm_z FOV
		else if (line[0] == 'C')
		{
			float px, py, pz, nx, ny, nz, f;
			if (sscanf(line, "C %f,%f,%f %f,%f,%f %f", &px, &py, &pz, &nx, &ny,
					&nz, &f) == 7)
			{
				camPos = (t_vec3){px, py, pz};
				camDir = vec3_normalize((t_vec3){nx, ny, nz});
				fov = f;
				yaw = atan2f(camDir.x, -camDir.z);
				pitch = asinf(camDir.y);
				printf("Camera : pos=(%.2f,%.2f,%.2f), dir=(%.2f,%.2f,%.2f),
					fov=%.2f\n", px, py, pz, nx, ny, nz, f);
			}
		}
		// Light: L pos_x,pos_y,pos_z brightness R,G,B
		else if (line[0] == 'L')
		{
			float lx, ly, lz, bright;
			int r, g, b;
			if (sscanf(line, "L %f,%f,%f %f %d,%d,%d", &lx, &ly, &lz, &bright,
					&r, &g, &b) == 7)
			{
				if (numLights < MAX_LIGHTS)
				{
					lights[numLights].pos = (t_vec3){lx, ly, lz};
					lights[numLights].brightness = bright;
					lights[numLights].color = (t_vec3){r / 255.0f, g / 255.0f, b
						/ 255.0f};
					numLights++;
					printf("Light : pos=(%.2f,%.2f,%.2f), bright=%.2f,
						color=(%d,%d,%d)\n", lx, ly, lz, bright, r, g, b);
				}
			}
		}
		// Sphere: sp pos_x,pos_y,pos_z diameter R,G,B
		else if (strncmp(line, "sp", 2) == 0)
		{
			float cx, cy, cz, diam;
			int r, g, b;
			if (sscanf(line, "sp %f,%f,%f %f %d,%d,%d", &cx, &cy, &cz, &diam,
					&r, &g, &b) == 7)
			{
				if (numSpheres < MAX_SPHERES)
				{
					spheres[numSpheres].center = (t_vec3){cx, cy, cz};
					spheres[numSpheres].radius = diam / 2.0f;
					spheres[numSpheres].color = (t_vec3){r / 255.0f, g / 255.0f,
						b / 255.0f};
					numSpheres++;
					printf("Sphere : center=(%.2f,%.2f,%.2f), diam=%.2f,
						color=(%d,%d,%d)\n", cx, cy, cz, diam, r, g, b);
				}
			}
		}
		// Plane: pl pos_x,pos_y,pos_z norm_x,norm_y,norm_z R,G,B
		else if (strncmp(line, "pl", 2) == 0)
		{
			float px, py, pz, nx, ny, nz;
			int r, g, b;
			// Correction : nous attendons 9 éléments (3 + 3 + 3)
			if (sscanf(line, "pl %f,%f,%f %f,%f,%f %d,%d,%d", &px, &py, &pz,
					&nx, &ny, &nz, &r, &g, &b) == 9)
			{
				if (numPlanes < MAX_PLANES)
				{
					planes[numPlanes].point = (t_vec3){px, py, pz};
					planes[numPlanes].normal = vec3_normalize((t_vec3){nx, ny,
							nz});
					planes[numPlanes].color = (t_vec3){r / 255.0f, g / 255.0f, b
						/ 255.0f};
					numPlanes++;
					printf("Plane : point=(%.2f,%.2f,%.2f),
						normal=(%.2f,%.2f,%.2f), color=(%d,%d,%d)\n", px, py,
						pz, nx, ny, nz, r, g, b);
				}
			}
		}
		// Cylinder: cy pos_x,pos_y,pos_z axis_x,axis_y,axis_z diameter height R,G,B
		else if (strncmp(line, "cy", 2) == 0)
		{
			float cx, cy, cz, ax, ay, az, diam, height;
			int r, g, b;
			// Correction : nous attendons 11 éléments (3 + 3 + 1 + 1 + 3)
			if (sscanf(line, "cy %f,%f,%f %f,%f,%f %f %f %d,%d,%d", &cx, &cy,
					&cz, &ax, &ay, &az, &diam, &height, &r, &g, &b) == 11)
			{
				if (numCylinders < MAX_CYLINDERS)
				{
					cylinders[numCylinders].center = (t_vec3){cx, cy, cz};
					cylinders[numCylinders].axis = vec3_normalize((t_vec3){ax,
							ay, az});
					cylinders[numCylinders].radius = diam / 2.0f;
					cylinders[numCylinders].height = height;
					cylinders[numCylinders].color = (t_vec3){r / 255.0f, g
						/ 255.0f, b / 255.0f};
					numCylinders++;
					printf("Cylinder : center=(%.2f,%.2f,%.2f),
						axis=(%.2f,%.2f,%.2f), diam=%.2f, height=%.2f,
						color=(%d,%d,%d)\n", cx, cy, cz, ax, ay, az, diam,
						height, r, g, b);
				}
			}
		}
	}
	fclose(fp);
}

// ----- Fonctions d'intersection -----
float	intersectSphere(Ray ray, Sphere s, t_vec3 *hitNormal)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	disc;
	float	sqrtDisc;
	float	t0;
	float	t1;
	float	t;
	t_vec3	hitPoint;

	oc = vec3_sub(ray.origin, s.center);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0f * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - s.radius * s.radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (-1);
	sqrtDisc = sqrtf(disc);
	t0 = (-b - sqrtDisc) / (2 * a);
	t1 = (-b + sqrtDisc) / (2 * a);
	t = (t0 > 1e-3f) ? t0 : t1;
	if (t < 1e-3f)
		return (-1);
	hitPoint = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	*hitNormal = vec3_normalize(vec3_sub(hitPoint, s.center));
	return (t);
}

float	intersectPlane(Ray ray, Plane p, t_vec3 *hitNormal)
{
	float	denom;
	float	t;

	denom = vec3_dot(p.normal, ray.dir);
	if (fabs(denom) < 1e-6f)
		return (-1);
	t = vec3_dot(vec3_sub(p.point, ray.origin), p.normal) / denom;
	if (t < 1e-3f)
		return (-1);
	*hitNormal = p.normal;
	return (t);
}

// Intersection d'un cylindre orienté arbitrairement (version simplifiée)
float	intersectCylinder(Ray ray, Cylinder cy, t_vec3 *hitNormal)
{
	t_vec3	d;
	t_vec3	oc;
	t_vec3	v;
	float	d_dot_v;
	float	oc_dot_v;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	float	a;
	float	b;
	float	c;
	float	disc;
	float	sqrtDisc;
	float	t0;
	float	t1;
	float	t_side;
	float	y;
	float	y;
	float	t_cap;
	float	t_bot;
	t_vec3	p;
	t_vec3	cp;
	float	dist;
	float	t_top;
	t_vec3	p;
	t_vec3	cp;
	float	dist;
	float	t_final;
	t_vec3	hitPoint;
	t_vec3	cp;
	float	proj;
	t_vec3	n;

	d = ray.dir;
	oc = vec3_sub(ray.origin, cy.center);
	v = cy.axis;
	d_dot_v = vec3_dot(d, v);
	oc_dot_v = vec3_dot(oc, v);
	d_perp = vec3_sub(d, vec3_scale(v, d_dot_v));
	oc_perp = vec3_sub(oc, vec3_scale(v, oc_dot_v));
	a = vec3_dot(d_perp, d_perp);
	b = 2 * vec3_dot(d_perp, oc_perp);
	c = vec3_dot(oc_perp, oc_perp) - cy.radius * cy.radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (-1);
	sqrtDisc = sqrtf(disc);
	t0 = (-b - sqrtDisc) / (2 * a);
	t1 = (-b + sqrtDisc) / (2 * a);
	t_side = -1;
	if (t0 > 1e-3f)
	{
		y = oc_dot_v + t0 * d_dot_v;
		if (fabs(y) <= cy.height / 2.0f)
			t_side = t0;
	}
	if (t_side < 0 && t1 > 1e-3f)
	{
		y = oc_dot_v + t1 * d_dot_v;
		if (fabs(y) <= cy.height / 2.0f)
			t_side = t1;
	}
	t_cap = -1;
	if (fabs(d_dot_v) > 1e-6f)
	{
		t_bot = ((-cy.height / 2.0f) - oc_dot_v) / d_dot_v;
		if (t_bot > 1e-3f)
		{
			p = vec3_add(ray.origin, vec3_scale(d, t_bot));
			cp = vec3_sub(p, cy.center);
			dist = vec3_length(vec3_sub(cp, vec3_scale(v, vec3_dot(cp, v))));
			if (dist <= cy.radius)
				t_cap = t_bot;
		}
		t_top = ((cy.height / 2.0f) - oc_dot_v) / d_dot_v;
		if (t_top > 1e-3f)
		{
			p = vec3_add(ray.origin, vec3_scale(d, t_top));
			cp = vec3_sub(p, cy.center);
			dist = vec3_length(vec3_sub(cp, vec3_scale(v, vec3_dot(cp, v))));
			if (dist <= cy.radius && (t_cap < 0 || t_top < t_cap))
				t_cap = t_top;
		}
	}
	t_final = -1;
	if (t_side > 1e-3f && t_cap > 1e-3f)
		t_final = (t_side < t_cap) ? t_side : t_cap;
	else if (t_side > 1e-3f)
		t_final = t_side;
	else
		t_final = t_cap;
	if (t_final < 1e-3f)
		return (-1);
	hitPoint = vec3_add(ray.origin, vec3_scale(d, t_final));
	cp = vec3_sub(hitPoint, cy.center);
	proj = vec3_dot(cp, v);
	if (fabs(proj) < cy.height / 2.0f - 1e-3f)
	{
		n = vec3_sub(cp, vec3_scale(v, proj));
		*hitNormal = vec3_normalize(n);
	}
	else
	{
		*hitNormal = (proj > 0) ? v : vec3_scale(v, -1);
	}
	return t_final;
}

// ----- Test d'ombre -----
bool	isInShadow(t_vec3 hitPoint, t_vec3 lightPos)
{
	t_vec3		toLight;
	float		maxT;
	t_vec3		L;
	const float	epsilon = 1e-3f;
	Ray			shadowRay;
	t_vec3		dummy;
	float		t;

	toLight = vec3_sub(lightPos, hitPoint);
	maxT = vec3_length(toLight);
	L = vec3_normalize(toLight);
	shadowRay = {vec3_add(hitPoint, vec3_scale(L, epsilon)), L};
	for (int i = 0; i < numSpheres; i++)
	{
		t = intersectSphere(shadowRay, spheres[i], &dummy);
		if (t > epsilon && t < maxT)
			return true;
	}
	for (int i = 0; i < numPlanes; i++)
	{
		t = intersectPlane(shadowRay, planes[i], &dummy);
		if (t > epsilon && t < maxT)
			return true;
	}
	for (int i = 0; i < numCylinders; i++)
	{
		t = intersectCylinder(shadowRay, cylinders[i], &dummy);
		if (t > epsilon && t < maxT)
			return true;
	}
	return false;
}

// ----- Lancer de rayon (ray tracing) -----
t_vec3	trace(Ray ray)
{
	float	tMin;
	t_vec3	hitNormal;
	t_vec3	objColor;
	bool	hitSomething;
	float	t;
		t_vec3 n;
		t_vec3 n;
		t_vec3 n;
	t_vec3	hitPoint;
	t_vec3	finalColor;
	Light	light;
	t_vec3	L;
	float	diff;
	t_vec3	viewDir;
	t_vec3	halfDir;
	float	spec;

	tMin = 1e9;
	hitNormal = {0, 0, 0};
	objColor = {0, 0, 0};
	hitSomething = false;
	for (int i = 0; i < numSpheres; i++)
	{
		t = intersectSphere(ray, spheres[i], &n);
		if (t > 1e-3f && t < tMin)
		{
			tMin = t;
			hitNormal = n;
			objColor = spheres[i].color;
			hitSomething = true;
		}
	}
	for (int i = 0; i < numPlanes; i++)
	{
		t = intersectPlane(ray, planes[i], &n);
		if (t > 1e-3f && t < tMin)
		{
			tMin = t;
			hitNormal = n;
			objColor = planes[i].color;
			hitSomething = true;
		}
	}
	for (int i = 0; i < numCylinders; i++)
	{
		t = intersectCylinder(ray, cylinders[i], &n);
		if (t > 1e-3f && t < tMin)
		{
			tMin = t;
			hitNormal = n;
			objColor = cylinders[i].color;
			hitSomething = true;
		}
	}
	if (hitSomething)
	{
		hitPoint = vec3_add(ray.origin, vec3_scale(ray.dir, tMin));
		finalColor = vec3_scale(objColor, ambient_ratio);
		for (int i = 0; i < numLights; i++)
		{
			light = lights[i];
			L = vec3_normalize(vec3_sub(light.pos, hitPoint));
			if (isInShadow(hitPoint, light.pos))
				continue ;
			diff = fmaxf(0.0f, vec3_dot(hitNormal, L));
			viewDir = vec3_normalize(vec3_sub(camPos, hitPoint));
			halfDir = vec3_normalize(vec3_add(L, viewDir));
			spec = powf(fmaxf(0.0f, vec3_dot(hitNormal, halfDir)), 32.0f);
			finalColor = vec3_add(finalColor, vec3_scale(vec3_mul(objColor,
							light.color), diff * light.brightness));
			finalColor = vec3_add(finalColor, vec3_scale((t_vec3){1, 1, 1}, spec
						* light.brightness));
		}
		if (finalColor.x > 1.0f)
			finalColor.x = 1.0f;
		if (finalColor.y > 1.0f)
			finalColor.y = 1.0f;
		if (finalColor.z > 1.0f)
			finalColor.z = 1.0f;
		return finalColor;
	}
	return (t_vec3){0.2f, 0.7f, 1.0f}; // Fond (ciel)
}

// ----- Main -----
int	main(int argc, char *argv[])
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	Uint32			*pixels;
	bool			running;
	SDL_Event		event;
	const float		moveSpeed = 0.5f;
	const float		rotSpeed = 0.03f;
	const float		mouseSensitivity = 0.002f;
	bool			key_w = false, key_s = false, key_a = false, key_d;
	bool			key_left = false, key_right = false, key_up = false,
					key_down;
	t_vec3			right;
	t_vec3			camUp;
	float			ndc_x;
	float			ndc_y;
	float			aspect;
	float			scale;
	float			screen_x;
	float			screen_y;
	t_vec3			rayDir;
	Ray				ray;
	t_vec3			color;
	Uint8			r;
	Uint8			g;
	Uint8			b;

	// Chargement de la config si un fichier est passé en argument
	if (argc > 1)
		load_config(argv[1]);
	// Scène par défaut si aucune config n'a été chargée
	if (numSpheres == 0 && numPlanes == 0 && numCylinders == 0
		&& numLights == 0)
	{
		spheres[0].center = (t_vec3){0, 0, 0};
		spheres[0].radius = 1.0f;
		spheres[0].color = (t_vec3){1, 0, 0};
		numSpheres = 1;
		planes[0].point = (t_vec3){0, -5, 0};
		planes[0].normal = (t_vec3){0, 1, 0};
		planes[0].color = (t_vec3){0, 1, 0};
		numPlanes = 1;
		cylinders[0].center = (t_vec3){10, 0, 0};
		cylinders[0].axis = (t_vec3){0, 1, 0};
		cylinders[0].radius = 4.0f;
		cylinders[0].height = 20.0f;
		cylinders[0].color = (t_vec3){0, 0, 1};
		numCylinders = 1;
		lights[0].pos = (t_vec3){0, 50, 20};
		lights[0].brightness = 1.0f;
		lights[0].color = (t_vec3){1, 1, 1};
		numLights = 1;
		ambient_ratio = 0.3f;
		ambient_color = (t_vec3){1, 1, 1};
		camPos = (t_vec3){0, 0, 20};
		camDir = vec3_normalize((t_vec3){0, 0, -1});
		fov = 70.0f;
		yaw = atan2f(camDir.x, -camDir.z);
		pitch = asinf(camDir.y);
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow("Raytracer interactif", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH * 2, HEIGHT * 2, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Erreur SDL_CreateWindow: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (!texture)
	{
		fprintf(stderr, "Erreur SDL_CreateTexture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	pixels = malloc(WIDTH * HEIGHT * sizeof(Uint32));
	if (!pixels)
	{
		fprintf(stderr, "Erreur d'allocation mémoire.\n");
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	running = true;
	key_w = false, key_s = false, key_a = false, key_d = false;
	key_left = false, key_right = false, key_up = false, key_down = false;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					break ;
				case SDLK_w:
					key_w = true;
					break ;
				case SDLK_s:
					key_s = true;
					break ;
				case SDLK_a:
					key_a = true;
					break ;
				case SDLK_d:
					key_d = true;
					break ;
				case SDLK_LEFT:
					key_left = true;
					break ;
				case SDLK_RIGHT:
					key_right = true;
					break ;
				case SDLK_UP:
					key_up = true;
					break ;
				case SDLK_DOWN:
					key_down = true;
					break ;
				default:
					break ;
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					key_w = false;
					break ;
				case SDLK_s:
					key_s = false;
					break ;
				case SDLK_a:
					key_a = false;
					break ;
				case SDLK_d:
					key_d = false;
					break ;
				case SDLK_LEFT:
					key_left = false;
					break ;
				case SDLK_RIGHT:
					key_right = false;
					break ;
				case SDLK_UP:
					key_up = false;
					break ;
				case SDLK_DOWN:
					key_down = false;
					break ;
				default:
					break ;
				}
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				yaw += event.motion.xrel * mouseSensitivity;
				pitch -= event.motion.yrel * mouseSensitivity;
			}
		}
		if (key_left)
			yaw -= rotSpeed;
		if (key_right)
			yaw += rotSpeed;
		if (key_up)
			pitch += rotSpeed;
		if (key_down)
			pitch -= rotSpeed;
		if (pitch > 1.57f - 0.01f)
			pitch = 1.57f - 0.01f;
		if (pitch < -1.57f + 0.01f)
			pitch = -1.57f + 0.01f;
		camDir.x = cosf(pitch) * sinf(yaw);
		camDir.y = sinf(pitch);
		camDir.z = -cosf(pitch) * cosf(yaw);
		camDir = vec3_normalize(camDir);
		right = {cosf(yaw), 0, sinf(yaw)};
		right = vec3_normalize(right);
		camUp = vec3_normalize(vec3_cross(right, camDir));
		if (key_w)
			camPos = vec3_add(camPos, vec3_scale(camDir, moveSpeed));
		if (key_s)
			camPos = vec3_sub(camPos, vec3_scale(camDir, moveSpeed));
		if (key_a)
			camPos = vec3_sub(camPos, vec3_scale(right, moveSpeed));
		if (key_d)
			camPos = vec3_add(camPos, vec3_scale(right, moveSpeed));
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				ndc_x = (x + 0.5f) / WIDTH;
				ndc_y = (y + 0.5f) / HEIGHT;
				aspect = (float)WIDTH / HEIGHT;
				scale = tanf((fov * 0.5f) * (M_PI / 180.0f));
				screen_x = (2 * ndc_x - 1) * aspect * scale;
				screen_y = (1 - 2 * ndc_y) * scale;
				rayDir = vec3_add(camDir, vec3_add(vec3_scale(right, screen_x),
							vec3_scale(camUp, screen_y)));
				rayDir = vec3_normalize(rayDir);
				ray = {camPos, rayDir};
				color = trace(ray);
				r = (Uint8)(fminf(color.x, 1.0f) * 255);
				g = (Uint8)(fminf(color.y, 1.0f) * 255);
				b = (Uint8)(fminf(color.z, 1.0f) * 255);
				pixels[y * WIDTH + x] = (255 << 24) | (r << 16) | (g << 8) | b;
			}
		}
		SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	free(pixels);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
