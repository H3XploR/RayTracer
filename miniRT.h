/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:02:36 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 19:21:06 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "float.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// ----- Taille ecran ----
# define WIDTH 640
# define HEIGHT 480

// ----- Tableaux de la scène -----
# define MAX_SPHERES 128
# define MAX_PLANES 128
# define MAX_CYLINDERS 128
# define MAX_LIGHTS 1
# define MAX_AMBIENT 1
# define MAX_CAMERA 1

// ----- Espace 3d
typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

// ----- Ray -----
typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		dir;
}				t_ray;

// ----- Objets de la scène -----
typedef struct s_sphere
{
	t_vec3		center;
	float		radius;
	t_vec3		color;
}				t_sphere;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_vec3		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		axis;
	float		radius;
	float		height;
	t_vec3		color;
}				t_cylinder;

typedef struct s_light
{
	t_vec3		pos;
	float		brightness;
	t_vec3		color;
}				t_light;

typedef struct s_ambient
{
	float		ratio;
	t_vec3		color;
}				t_ambient;

typedef struct s_hit
{
	float		t;
	t_vec3		normal;
	t_vec3		color;
}				t_hit;

typedef struct s_hit_info
{
	t_vec3		point;
	t_vec3		normal;
	t_vec3		color;
}				t_hit_info;

typedef struct s_camera
{
	t_vec3		cam_pos;
	t_vec3		cam_dir;
	t_vec3		right;
	t_vec3		up;
	float		rot_speed;
	float		move_speed;
	float		fov;
	float		yaw;
	float		pitch;
}				t_camera;

typedef struct s_scene
{
	t_sphere	spheres[MAX_SPHERES];
	t_plane		planes[MAX_PLANES];
	t_cylinder	cylinders[MAX_CYLINDERS];
	t_light		lights[MAX_LIGHTS];
	t_ambient	ambient;
	t_camera	camera;
	t_ray		ray;
	int			problem;
	int			num_spheres;
	int			num_planes;
	int			num_cylinders;
	int			num_camera;
	int			num_lights;
	int			num_ambient;
	char		*line_if_exit;
	char		**token_if_exit;
	char		**all_file;
	int			fd_if_exit;
}				t_scene;

// ----- Minilibx
typedef struct s_app
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*pixels;
	int			bpp;
	int			size_line;
	int			endian;
	int			win_width;
	int			win_height;
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
	int			key_up;
	int			key_down;
	float		mouse_sens;
	t_scene		scene;
}				t_app;

// ----- Calcul
typedef struct s_calc
{
	t_vec3		oc;
	float		a;
	float		b;
	float		c;
	float		disc;
	float		sqrt_disc;
	float		t0;
	float		t1;
	float		t;
	t_vec3		hit_point;
	t_vec3		d;
	t_vec3		v;
	float		d_dot_v;
	float		oc_dot_v;
	t_vec3		d_perp;
	t_vec3		oc_perp;
	float		t_side;
	float		y;
	float		t_cap;
	float		t_bot;
	float		t_top;
	t_vec3		p;
	t_vec3		cp;
	float		dist;
	float		t_final;
	float		proj;
	t_vec3		n;
	float		ndc_x;
	float		ndc_y;
	float		aspect;
	float		scale;
	float		screen_x;
	float		screen_y;
	t_ray		ray;
	t_vec3		ray_dir;
	t_vec3		color;
	t_light		light;
	t_vec3		l;
	float		diff;
	t_vec3		view_dir;
	t_vec3		half_dir;
	float		spec;

}				t_calc;

//	Calcul de vecteur
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_scale(t_vec3 a, float s);
float			vec3_dot(t_vec3 a, t_vec3 b);
t_vec3			vec3_cross(t_vec3 a, t_vec3 b);
float			vec3_length(t_vec3 a);
t_vec3			vec3_normalize(t_vec3 a);
t_vec3			vec3_mul(t_vec3 a, t_vec3 b);

//	Config de scene
t_scene			create_scene(void);
t_scene			load_config(const char *filename);
t_scene			parsing_ambiant(t_scene scene);
t_scene			parsing_camera(t_scene scene);
t_scene			parsing_light(t_scene scene);
t_scene			parsing_sphere(t_scene scene);
t_scene			parsing_plane(t_scene scene);
t_scene			parsing_cylindre(t_scene scene);
t_vec3			parse_color(const char *token, t_scene scene);
t_vec3			parse_vector(const char *token, t_scene scene);
t_vec3			parse_vector_normalize(const char *token, t_scene scene);

//	Parsing utils
char			**get_tokens_secure(t_scene scene, const int numObject,
					const int numObjectMax, const int supposed_nb_token);

//	Check
int				check_tokens(char **tokens, int expected);
int				isdigit_token(char **tokens);
int				have_extension(const char *line);
int				check_if_max(t_scene scene, const int to_test, const int max);

//	Intersection
float			intersect_cylinder(t_ray ray, t_cylinder cy, t_vec3 *hitNormal);
float			intersect_plane(t_ray ray, t_plane p, t_vec3 *hitNormal);
float			intersect_sphere(t_ray ray, t_sphere s, t_vec3 *hitNormal);
bool			is_in_shadow(t_vec3 hitPoint, t_vec3 lightPos, t_scene scene);
bool			intersect_objects(float *tMin, t_vec3 *hitNormal,
					t_vec3 *objColor, t_scene scene);
t_vec3			calc_lighting(t_vec3 hitPoint, t_vec3 hitNormal,
					t_vec3 objColor, t_scene scene);
t_vec3			trace(t_ray ray, t_scene scene);

//	Interesction utils cylindre
int				init_intersection(t_ray ray, t_cylinder cy, t_calc *calc);
void			compute_side_intersection(t_cylinder cy, t_calc *calc);
void			compute_cap_intersection(t_ray ray, t_cylinder cy,
					t_calc *calc);
float			select_final_intersection(t_calc *calc);
void			compute_hit_normal(t_ray ray, t_cylinder cy, t_calc *calc,
					t_vec3 *hitNormal);

//	Peripherique
int				key_press(int keycode, t_app *app);
int				handle_close(void *param);

//	Render
void			update_camera(t_app *app);
void			render_scene(t_app *app);

//	Array
int				ft_arraylen(char **array);
void			ft_free_array(char **array);

//	Conversion
float			ft_atof(char *str);

//	Info
void			print_vec3(t_vec3 vec);
void			print_ray(t_ray ray);
void			print_sphere(t_sphere sphere);
void			print_plane(t_plane plane);
void			print_cylinder(t_cylinder cyl);
void			print_light(t_light light);
void			print_ambient(t_ambient amb);
void			print_camera(t_camera cam);
void			print_scene(t_scene scene);

//	Memoire
void			*ft_realloc(void *ptr, \
				size_t old_size, size_t new_size);
#endif
