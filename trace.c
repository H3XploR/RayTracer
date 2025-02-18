/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:07:07 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/18 17:15:32 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Renvoie true si le rayon intersecte un objet, et met à jour tMin,
//hitNormal et objColor
bool	intersectObjects(t_ray ray, float *tMin, t_vec3 *hitNormal,
		t_vec3 *objColor, t_scene scene)
{
	bool	hit;
	float	t;
	t_vec3	n;
	int		i;

	hit = false;
	i = 0;
	while (i < scene.numSpheres)
	{
		t = intersectSphere(ray, scene.spheres[i], &n);
		if (t > 1e-3f && t < *tMin)
		{
			*tMin = t;
			*hitNormal = n;
			*objColor = scene.spheres[i].color;
			hit = true;
		}
		i++;
	}
	i = 0;
	while (i < scene.numPlanes)
	{
		t = intersectPlane(ray, scene.planes[i], &n);
		if (t > 1e-3f && t < *tMin)
		{
			*tMin = t;
			*hitNormal = n;
			*objColor = scene.planes[i].color;
			hit = true;
		}
		i++;
	}
	i = 0;
	while (i < scene.numCylinders)
	{
		t = intersectCylinder(ray, scene.cylinders[i], &n);
		if (t > 1e-3f && t < *tMin)
		{
			*tMin = t;
			*hitNormal = n;
			*objColor = scene.cylinders[i].color;
			hit = true;
		}
		i++;
	}
	return (hit);
}

// Calcule l'éclairage (ambiant, diffus et spéculaire) sur un point d'impact
t_vec3	calcLighting(t_vec3 hitPoint, t_vec3 hitNormal, t_vec3 objColor,
		t_scene scene)
{
	t_vec3	color;
	int		i;
	t_light	light;
	t_vec3	L;
	float	diff;
	t_vec3	viewDir;
	t_vec3	halfDir;
	float	spec;

	color = vec3_scale(objColor, scene.ambient.ratio);
	i = 0;
	while (i < scene.numLights)
	{
		light = scene.lights[i];
		L = vec3_normalize(vec3_sub(light.pos, hitPoint));
		if (!isInShadow(hitPoint, light.pos, scene))
		{
			diff = fmaxf(0.0f, vec3_dot(hitNormal, L));
			viewDir = vec3_normalize(vec3_sub(scene.camera.camPos, hitPoint));
			halfDir = vec3_normalize(vec3_add(L, viewDir));
			spec = powf(fmaxf(0.0f, vec3_dot(hitNormal, halfDir)), 32.0f);
			color = vec3_add(color, vec3_scale(vec3_mul(objColor, light.color),
						diff * light.brightness));
			color = vec3_add(color, vec3_scale((t_vec3){1, 1, 1}, spec
						* light.brightness));
		}
		i++;
	}
	if (color.x > 1.0f)
		color.x = 1.0f;
	if (color.y > 1.0f)
		color.y = 1.0f;
	if (color.z > 1.0f)
		color.z = 1.0f;
	return (color);
}

// Fonction principale de lancer de rayon (trace)
t_vec3	trace(t_ray ray, t_scene scene)
{
	float	tMin;
	t_vec3	hitNormal;
	t_vec3	objColor;
	t_vec3	hitPoint;

	tMin = 1e9;
	hitNormal = (t_vec3){0, 0, 0};
	objColor = (t_vec3){0, 0, 0};
	if (intersectObjects(ray, &tMin, &hitNormal, &objColor, scene))
	{
		hitPoint = vec3_add(ray.origin, vec3_scale(ray.dir, tMin));
		return (calcLighting(hitPoint, hitNormal, objColor, scene));
	}
	return ((t_vec3){0.2f, 0.7f, 1.0f}); // Couleur de fond (ciel)
}
