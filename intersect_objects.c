/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:07:55 by yantoine          #+#    #+#             */
/*   Updated: 2025/03/05 14:19:33 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	intersect_spheres(const t_ray ray, t_hit *hit, t_sphere *spheres,
		int num_spheres)
{
	int		i;
	bool	hit_any;
	t_vec3	n;
	float	t;

	i = 0;
	hit_any = false;
	while (i < num_spheres)
	{
		t = intersect_sphere(ray, spheres[i], &n);
		if (t > 0.001f && t < hit->t)
		{
			hit->t = t;
			hit->normal = n;
			hit->color = spheres[i].color;
			hit_any = true;
		}
		i++;
	}
	return (hit_any);
}

static bool	intersect_planes(const t_ray ray, t_hit *hit, t_plane *planes,
		int num_planes)
{
	int		i;
	bool	hit_any;
	t_vec3	n;
	float	t;

	i = 0;
	hit_any = false;
	while (i < num_planes)
	{
		t = intersect_plane(ray, planes[i], &n);
		if (t > 0.001f && t < hit->t)
		{
			hit->t = t;
			hit->normal = n;
			hit->color = planes[i].color;
			hit_any = true;
		}
		i++;
	}
	return (hit_any);
}

static bool	intersect_cylinders(const t_ray ray, t_hit *hit,
		t_cylinder *cylinders, int num_cylinders)
{
	int		i;
	bool	hit_any;
	t_vec3	n;
	float	t;

	i = 0;
	hit_any = false;
	while (i < num_cylinders)
	{
		t = intersect_cylinder(ray, cylinders[i], &n);
		if (t > 0.001f && t < hit->t)
		{
			hit->t = t;
			hit->normal = n;
			hit->color = cylinders[i].color;
			hit_any = true;
		}
		i++;
	}
	return (hit_any);
}

bool	intersect_objects(float *tMin, t_vec3 *hitNormal, t_vec3 *objColor,
		t_scene scene)
{
	t_hit	hit;
	bool	hit_found;

	hit_found = false;
	hit.t = *tMin;
	if (intersect_spheres(scene.ray, &hit, scene.spheres, scene.num_spheres))
		hit_found = true;
	if (intersect_planes(scene.ray, &hit, scene.planes, scene.num_planes))
		hit_found = true;
	if (intersect_cylinders(scene.ray, &hit, scene.cylinders,
			scene.num_cylinders))
		hit_found = true;
	if (hit_found)
	{
		*tMin = hit.t;
		*hitNormal = hit.normal;
		*objColor = hit.color;
	}
	return (hit_found);
}
