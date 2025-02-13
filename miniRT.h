/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:02:36 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/13 20:16:50 by yantoine         ###   ########.fr       */
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
	float	x;
	float	y;
	float	z;
}			t_vec3;

// ----- Ray -----
typedef struct s_vec3
{
	t_vec3	origin;
	t_vec3	dir;
}			t_ray;

// ----- Objets de la scène -----
typedef struct s_vec3
{
	t_vec3	center;
	float	radius;
	t_vec3	color;
}			t_sphere;

typedef struct s_vec3
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
}			t_plane;

typedef struct s_vec3
{
	t_vec3	center;
	t_vec3	axis;// Axe normalisé
	float	radius;// Demi-diamètre
	float	height;
	t_vec3	color;
}			t_cylinder;

typedef struct s_vec3
{
	t_vec3	pos;
	float	brightness;
	t_vec3	color;
}			t_light;


//	Calcul de vecteur
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 a, float s);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
float	vec3_length(t_vec3 a);
t_vec3	vec3_normalize(t_vec3 a);
t_vec3	vec3_mul(t_vec3 a, t_vec3 b);
#endif
