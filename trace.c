/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:07:07 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/19 16:30:27 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Calcule l'éclairage (ambiant, diffus et spéculaire) sur un point d'impact
t_vec3	calc_lighting(t_vec3 hitPoint, t_vec3 hitNormal, t_vec3 objColor,
		t_scene scene)
{
	int		i;
	t_calc		calc;

	calc.color = vec3_scale(objColor, scene.ambient.ratio);
	i = 0;
	while (i < scene.numLights)
	{
		calc.light = scene.lights[i];
		calc.l = vec3_normalize(vec3_sub(calc.light.pos, hitPoint));
		if (!is_in_shadow(hitPoint, calc.light.pos, scene))
		{
			calc.diff = fmaxf(0.0f, vec3_dot(hitNormal, calc.l));
			calc.view_dir = vec3_normalize(vec3_sub(scene.camera.camPos, hitPoint));
			calc.half_dir = vec3_normalize(vec3_add(calc.l, calc.view_dir));
			calc.spec = powf(fmaxf(0.0f, vec3_dot(hitNormal, calc.half_dir)), 32.0f);
			calc.color = vec3_add(calc.color, vec3_scale(vec3_mul(objColor, calc.light.color),
						calc.diff * calc.light.brightness));
			calc.color = vec3_add(calc.color, vec3_scale((t_vec3){1, 1, 1}, calc.spec
						* calc.light.brightness));
		}
		i++;
	}
	if (calc.color.x > 1.0f)
		calc.color.x = 1.0f;
	if (calc.color.y > 1.0f)
		calc.color.y = 1.0f;
	if (calc.color.z > 1.0f)
		calc.color.z = 1.0f;
	return (calc.color);
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
	scene.ray = ray;
	if (intersect_objects(&tMin, &hitNormal, &objColor, scene))
	{
		hitPoint = vec3_add(scene.ray.origin, vec3_scale(scene.ray.dir, tMin));
		return (calc_lighting(hitPoint, hitNormal, objColor, scene));
	}
	return ((t_vec3){0, 0, 0}); // Couleur de fond (ciel)
}
