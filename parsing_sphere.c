/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:46:16 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 21:31:36 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_sphere(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.numSpheres, MAX_SPHERES, 4);
	scene.token_if_exit = tokens;
	scene.spheres[scene.numSpheres].center = parse_vector(tokens[1], scene);
	scene.spheres[scene.numSpheres].radius = ft_atof(tokens[2]) / 2.0f;
	scene.spheres[scene.numSpheres].color = parse_color(tokens[3], scene);
	ft_free_array(tokens);
	scene.numSpheres++;
	return (scene);
}

float	intersectSphere(t_ray ray, t_sphere s, t_vec3 *hitNormal)
{
	t_calc	calc;
	
	calc.oc = vec3_sub(ray.origin, s.center);
	calc.a = vec3_dot(ray.dir, ray.dir);
	calc.b = 2.0f * vec3_dot(calc.oc, ray.dir);
	calc.c = vec3_dot(calc.oc, calc.oc) - s.radius * s.radius;
	calc.disc = calc.b * calc.b - 4 * calc.a * calc.c;
	if (calc.disc < 0)
		return (-1);
	calc.sqrtDisc = sqrtf(calc.disc);
	calc.t0 = (-calc.b - calc.sqrtDisc) / (2 * calc.a);
	calc.t1 = (-calc.b + calc.sqrtDisc) / (2 * calc.a);
	calc.t = (calc.t0 > 1e-3f) ? calc.t0 : calc.t1;
	if (calc.t < 1e-3f)
		return (-1);
	calc.hitPoint = vec3_add(ray.origin, vec3_scale(ray.dir, calc.t));
	*hitNormal = vec3_normalize(vec3_sub(calc.hitPoint, s.center));
	return (calc.t);
}

