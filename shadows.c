/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:58:42 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 21:44:07 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Vérifie les intersections avec les sphères
static bool	checkShadowSphere(const t_ray shadowRay, float maxT, float epsilon,
		t_scene scene)
{
	int		i;
	t_vec3	dummy;
	float	t;

	i = 0;
	while (i < scene.numSpheres)
	{
		t = intersectSphere(shadowRay, scene.spheres[i], &dummy);
		if (t > epsilon && t < maxT)
			return (true);
		i++;
	}
	return (false);
}

// Vérifie les intersections avec les plans
static bool	checkShadowPlane(const t_ray shadowRay, float maxT, float epsilon,
		t_scene scene)
{
	int		i;
	t_vec3	dummy;
	float	t;

	i = 0;
	while (i < scene.numPlanes)
	{
		t = intersectPlane(shadowRay, scene.planes[i], &dummy);
		if (t > epsilon && t < maxT)
			return (true);
		i++;
	}
	return (false);
}

// Vérifie les intersections avec les cylindres
static bool	checkShadowCylinder(const t_ray shadowRay, float maxT,
		float epsilon, t_scene scene)
{
	int		i;
	t_vec3	dummy;
	float	t;

	i = 0;
	while (i < scene.numCylinders)
	{
		t = intersectCylinder(shadowRay, scene.cylinders[i], &dummy);
		if (t > epsilon && t < maxT)
			return (true);
		i++;
	}
	return (false);
}

// Fonction principale qui détermine si le point est dans l'ombre
bool	isInShadow(t_vec3 hitPoint, t_vec3 lightPos, t_scene scene)
{
	const float	epsilon = 1e-3f;
	t_vec3		toLight;
	float		maxT;
	t_vec3		L;
	t_ray		shadowRay;

	toLight = vec3_sub(lightPos, hitPoint);
	maxT = vec3_length(toLight);
	L = vec3_normalize(toLight);
	shadowRay.origin = vec3_add(hitPoint, vec3_scale(L, epsilon));
	shadowRay.dir = L;
	if (checkShadowSphere(shadowRay, maxT, epsilon, scene))
		return (true);
	if (checkShadowPlane(shadowRay, maxT, epsilon, scene))
		return (true);
	if (checkShadowCylinder(shadowRay, maxT, epsilon, scene))
		return (true);
	return (false);
}
