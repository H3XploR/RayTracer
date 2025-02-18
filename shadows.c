/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:58:42 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/18 17:48:22 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Vérifie les intersections avec les sphères
static bool	check_shadow_sphere(const t_ray shadow_ray, \
		float max_t, t_scene scene)
{
	const float	epsilon = 1e-3f;
	int		i;
	t_vec3	dummy;
	float	t;

	i = 0;
	while (i < scene.numSpheres)
	{
		t = intersectSphere(shadow_ray, scene.spheres[i], &dummy);
		if (t > epsilon && t < max_t)
			return (true);
		i++;
	}
	return (false);
}

// Vérifie les intersections avec les plans
static bool	check_shadow_plane(const t_ray shadow_ray, \
		float max_t, t_scene scene)
{
	const float	epsilon = 1e-3f;
	int		i;
	t_vec3	dummy;
	float	t;

	i = 0;
	while (i < scene.numPlanes)
	{
		t = intersectPlane(shadow_ray, scene.planes[i], &dummy);
		if (t > epsilon && t < max_t)
			return (true);
		i++;
	}
	return (false);
}

// Vérifie les intersections avec les cylindres
static bool	check_shadow_cylinder(const t_ray shadow_ray, \
		float max_t, t_scene scene)
{
	const float	epsilon = 1e-3f;
	int		i;
	t_vec3	dummy;
	float	t;

	i = 0;
	while (i < scene.numCylinders)
	{
		t = intersectCylinder(shadow_ray, scene.cylinders[i], &dummy);
		if (t > epsilon && t < max_t)
			return (true);
		i++;
	}
	return (false);
}

// Fonction principale qui détermine si le point est dans l'ombre
bool	is_in_shadow(t_vec3 hitPoint, t_vec3 lightPos, t_scene scene)
{
	const float	epsilon = 1e-3f;
	t_vec3		to_light;
	float		max_t;
	t_vec3		l;
	t_ray		shadow_ray;

	to_light = vec3_sub(lightPos, hitPoint);
	max_t = vec3_length(to_light);
	l = vec3_normalize(to_light);
	shadow_ray.origin = vec3_add(hitPoint, vec3_scale(l, epsilon));
	shadow_ray.dir = l;
	if (check_shadow_sphere(shadow_ray, max_t, scene))
		return (true);
	if (check_shadow_plane(shadow_ray, max_t, scene))
		return (true);
	if (check_shadow_cylinder(shadow_ray, max_t, scene))
		return (true);
	return (false);
}
