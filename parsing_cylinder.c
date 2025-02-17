/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:54:13 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 18:55:52 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
float	intersectCylinder(Ray ray, Cylinder cy, t_vec3 *hitNormal)
{
	t_calc calc;

	calc.d = ray.dir;
	calc.oc = vec3_sub(ray.origin, cy.center);
	calc.v = cy.axis;
	calc.d_dot_v = vec3_dot(calc.d, calc.v);
	calc.oc_dot_v = vec3_dot(calc.oc, calc.v);
	calc.d_perp = vec3_sub(calc.calc.d, vec3_scale(calc.v, calc.d_dot_v));
	oc_perp = vec3_sub(calc.oc, vec3_scale(calc.v, calc.oc_dot_v));
	calc.a = vec3_dot(calc.d_perp, calc.d_perp);
	calc.b = 2 * vec3_dot(calc.d_perp, oc_perp);
	calc.c = vec3_dot(oc_perp, oc_perp) - cy.radius * cy.radius;
	calc.disc = calc.b * calc.b - 4 * calc.a * calc.c;
	if (calc.disc < 0)
		return (-1);
	calc.sqrtDisc = sqrtf(calc.disc);
	calc.t0 = (-calc.b - calc.sqrtDisc) / (2 * calc.a);
	calc.t1 = (-calc.b + calc.sqrtDisc) / (2 * calc.a);
	calc.t_side = -1;
	if (calc.t0 > 1e-3f)
	{
		calc.y = calc.oc_dot_v + calc.t0 * calc.d_dot_v;
		if (fabs(calc.y) <= cy.height / 2.0f)
			calc.t_side = calc.t0;
	}
	if (calc.t_side < 0 && calc.t1 > 1e-3f)
	{
		calc.y = calc.oc_dot_v + calc.t1 * calc.d_dot_v;
		if (fabs(calc.y) <= cy.height / 2.0f)
			calc.t_side = calc.t1;
	}
	calc.t_cap = -1;
	if (fabs(calc.d_dot_v) > 1e-6f)
	{
		calc.t_bot = ((-cy.height / 2.0f) - calc.oc_dot_v) / calc.d_dot_v;
		if (calc.t_bot > 1e-3f)
		{
			p = vec3_add(ray.origin, vec3_scale(calc.d, calc.t_bot));
			cp = vec3_sub(p, cy.center);
			calc.dist = vec3_length(vec3_sub(cp, vec3_scale(calc.v, vec3_dot(cp, calc.v))));
			if (calc.dist <= cy.radius)
				calc.t_cap = calc.t_bot;
		}
		t_top = ((cy.height / 2.0f) - calc.oc_dot_v) / calc.d_dot_v;
		if (t_top > 1e-3f)
		{
			p = vec3_add(ray.origin, vec3_scale(calc.d, t_top));
			cp = vec3_sub(p, cy.center);
			calc.dist = vec3_length(vec3_sub(cp, vec3_scale(calc.v, vec3_dot(cp, calc.v))));
			if (calc.dist <= cy.radius && (calc.t_cap < 0 || t_top < calc.t_cap))
				calc.t_cap = t_top;
		}
	}
	calc.t_final = -1;
	if (calc.t_side > 1e-3f && calc.t_cap > 1e-3f)
		calc.t_final = (calc.t_side < calc.t_cap) ? calc.t_side : calc.t_cap;
	else if (calc.t_side > 1e-3f)
		calc.t_final = calc.t_side;
	else
		calc.t_final = calc.t_cap;
	if (calc.t_final < 1e-3f)
		return (-1);
	calc.hitPoint = vec3_add(ray.origin, vec3_scale(calc.d, calc.t_final));
	cp = vec3_sub(calc.hitPoint, cy.center);
	calc.proj = vec3_dot(cp, calc.v);
	if (fabs(calc.proj) < cy.height / 2.0f - 1e-3f)
	{
		calc.n = vec3_sub(cp, vec3_scale(calc.v, calc.proj));
		*hitNormal = vec3_normalize(calc.n);
	}
	else
	{
		*hitNormal = (calc.proj > 0) ? calc.v : vec3_scale(calc.v, -1);
	}
	return calc.t_final;
}*/

t_scene	parsing_cylinder(const char *line, t_scene scene)
{
	const char	**tokens = get_tokens_secure(scene, scene.numCylinders, MAX_CYLINDERS, 6);
	scene.token_if_exit = tokens;
	scene.cylinders[scene.numCylinders].center = parse_vector(tokens[1], scene);
	scene.cylinders[scene.numCylinders].axis = parse_vector_normalize(tokens[2], scene);
	scene.cylinders[scene.numCylinders].radius = parse_float(tokens[3], scene);
	scene.cylinders[scene.numCylinders].height = parse_float(tokens[4], scene);
	scene.cylinders[scene.numCylinders].color = parse_color(tokens[5], scene);
	ft_free_array(tokens);
	scene.numCylinders++;
	return (scene);
}


