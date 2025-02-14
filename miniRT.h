/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:02:36 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 01:50:11 by yantoine         ###   ########.fr       */
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
	int			numSpheres;
	int			numPlanes;
	int			numCylinders;
	int			numLights;
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
t_scene			create_scene(void);
int		load_config(const char *filename);
#endif
