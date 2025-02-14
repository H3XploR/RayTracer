/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:02:36 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 20:45:21 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <SDL2/SDL.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// ----- Taille ecran ----
# define WIDTH 320
# define HEIGHT 240

// ----- Tableaux de la scène -----
# define MAX_SPHERES 128
# define MAX_PLANES 128
# define MAX_CYLINDERS 128
# define MAX_LIGHTS 16
# define MAX_AMBIENT 1

// ----- Structures
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
	t_vec3 axis;  // Axe normalisé
	float radius; // Demi-diamètre
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
	float		ambient_ratio;
	t_vec3		ambient_color;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		camPos;
	t_vec3		camDir;
	float		fov;
	float		yaw;// vue de gauche a droite
	float		pitch; // vue de haut en bas en radians
}				t_camera;

typedef struct s_scene
{
	t_sphere	spheres[MAX_SPHERES];
	t_plane		planes[MAX_PLANES];
	t_cylinder	cylinders[MAX_CYLINDERS];
	t_light		lights[MAX_LIGHTS];
	t_ambient	ambient;
	int			numSpheres;
	int			numPlanes;
	int			numCylinders;
	int			numLights;
	int			numAmbient;
	const char 		*line;
}				t_scene;

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
t_scene			parsing_ambiant(const char *line, t_scene scene);
t_scene			parsing_camera(const char *line, t_scene scene);
t_scene			parsing_light(const char *line, t_scene scene);
t_scene			parsing_sphere(const char *line, t_scene scene);
t_scene			parsing_plane(const char *line, t_scene scene);
t_scene			parsing_cylindre(const char *line, t_scene scene);
t_color			parse_color(const char *token, t_scene scene);

//	Parsing utils
inline	char	**get_tokens_secure(t_scene scene, const int numObject, const int numObjectMax, const int supposed_nb_token);

//	Check
inline int	check_tokens(char **tokens, const int to_test, int expected);
inline void	check_if_max(t_scene scene, const int to_test, const int max);
#endif
