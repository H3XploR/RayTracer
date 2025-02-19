/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:07:55 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/19 16:16:52 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	intersect_spheres(const t_ray ray, t_hit *hit, t_sphere *spheres,
		int numSpheres)
{
	int		i;
	bool	hitAny;
		t_vec3 n;
	float	t;

	i = 0;
	hitAny = false;
	while (i < numSpheres)
	{
		t = intersect_sphere(ray, spheres[i], &n);
		if (t > 1e-3f && t < hit->t)
		{
			hit->t = t;
			hit->normal = n;
			hit->color = spheres[i].color;
			hitAny = true;
		}
		i++;
	}
	return (hitAny);
}

static bool	intersect_planes(const t_ray ray, t_hit *hit, t_plane *planes,
		int numPlanes)
{
	int		i;
	bool	hitAny;
		t_vec3 n;
	float	t;

	i = 0;
	hitAny = false;
	while (i < numPlanes)
	{
		t = intersect_plane(ray, planes[i], &n);
		if (t > 1e-3f && t < hit->t)
		{
			hit->t = t;
			hit->normal = n;
			hit->color = planes[i].color;
			hitAny = true;
		}
		i++;
	}
	return (hitAny);
}

static bool	intersect_cylinders(const t_ray ray, t_hit *hit,
		t_cylinder *cylinders, int numCylinders)
{
	int		i;
	bool	hitAny;
		t_vec3 n;
	float	t;

	i = 0;
	hitAny = false;
	while (i < numCylinders)
	{
		t = intersect_cylinder(ray, cylinders[i], &n);
		if (t > 1e-3f && t < hit->t)
		{
			hit->t = t;
			hit->normal = n;
			hit->color = cylinders[i].color;
			hitAny = true;
		}
		i++;
	}
	return (hitAny);
}

bool	intersect_objects(float *tMin, t_vec3 *hitNormal, t_vec3 *objColor,
		t_scene scene)
{
	t_hit	hit;
	bool	hitFound;

	hitFound = false;
	hit.t = *tMin;
	if (intersect_spheres(scene.ray, &hit, scene.spheres, scene.numSpheres))
		hitFound = true;
	if (intersect_planes(scene.ray, &hit, scene.planes, scene.numPlanes))
		hitFound = true;
	if (intersect_cylinders(scene.ray, &hit, scene.cylinders,
			scene.numCylinders))
		hitFound = true;
	if (hitFound)
	{
		*tMin = hit.t;
		*hitNormal = hit.normal;
		*objColor = hit.color;
	}
	return (hitFound);
}
