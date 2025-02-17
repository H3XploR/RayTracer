/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:54:45 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 21:28:56 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Initialise les variables de calcul et les coefficients du polynôme d'intersection
static int	init_intersection(t_ray ray, t_cylinder cy, t_calc *calc)
{
	calc->d = ray.dir;
	calc->oc = vec3_sub(ray.origin, cy.center);
	calc->v = cy.axis;
	calc->d_dot_v = vec3_dot(calc->d, calc->v);
	calc->oc_dot_v = vec3_dot(calc->oc, calc->v);
	calc->d_perp = vec3_sub(calc->d, vec3_scale(calc->v, calc->d_dot_v));
	calc->oc_perp = vec3_sub(calc->oc, vec3_scale(calc->v, calc->oc_dot_v));
	calc->a = vec3_dot(calc->d_perp, calc->d_perp);
	calc->b = 2 * vec3_dot(calc->d_perp, calc->oc_perp);
	calc->c = vec3_dot(calc->oc_perp, calc->oc_perp) - cy.radius * cy.radius;
	calc->disc = calc->b * calc->b - 4 * calc->a * calc->c;
	if (calc->disc < 0)
		return (-1);
	calc->sqrtDisc = sqrtf(calc->disc);
	calc->t0 = (-calc->b - calc->sqrtDisc) / (2 * calc->a);
	calc->t1 = (-calc->b + calc->sqrtDisc) / (2 * calc->a);
	return (0);
}

// Calcule l'intersection sur la surface latérale du cylindre
static void	compute_side_intersection(t_cylinder cy, t_calc *calc)
{
	calc->t_side = -1;
	if (calc->t0 > 1e-3f)
	{
		calc->y = calc->oc_dot_v + calc->t0 * calc->d_dot_v;
		if (fabs(calc->y) <= cy.height / 2.0f)
			calc->t_side = calc->t0;
	}
	if (calc->t_side < 0 && calc->t1 > 1e-3f)
	{
		calc->y = calc->oc_dot_v + calc->t1 * calc->d_dot_v;
		if (fabs(calc->y) <= cy.height / 2.0f)
			calc->t_side = calc->t1;
	}
}

// Calcule l'intersection sur les capuchons supérieur et inférieur
static void	compute_cap_intersection(t_ray ray, t_cylinder cy, t_calc *calc)
{
	calc->t_cap = -1;
	if (fabs(calc->d_dot_v) > 1e-6f)
	{
		calc->t_bot = ((-cy.height / 2.0f) - calc->oc_dot_v) / calc->d_dot_v;
		if (calc->t_bot > 1e-3f)
		{
			calc->p = vec3_add(ray.origin, vec3_scale(calc->d, calc->t_bot));
			calc->cp = vec3_sub(calc->p, cy.center);
			calc->dist = vec3_length(vec3_sub(calc->cp, vec3_scale(calc->v,
							vec3_dot(calc->cp, calc->v))));
			if (calc->dist <= cy.radius)
				calc->t_cap = calc->t_bot;
		}
		calc->t_top = ((cy.height / 2.0f) - calc->oc_dot_v) / calc->d_dot_v;
		if (calc->t_top > 1e-3f)
		{
			calc->p = vec3_add(ray.origin, vec3_scale(calc->d, calc->t_top));
			calc->cp = vec3_sub(calc->p, cy.center);
			calc->dist = vec3_length(vec3_sub(calc->cp, vec3_scale(calc->v,
							vec3_dot(calc->cp, calc->v))));
			if (calc->dist <= cy.radius && (calc->t_cap < 0
					|| calc->t_top < calc->t_cap))
				calc->t_cap = calc->t_top;
		}
	}
}

// Sélectionne l'intersection la plus proche entre la surface latérale et les capuchons
static float	select_final_intersection(t_calc *calc)
{
	if (calc->t_side > 1e-3f && calc->t_cap > 1e-3f)
		calc->t_final = (calc->t_side < calc->t_cap) ? calc->t_side : calc->t_cap;
	else if (calc->t_side > 1e-3f)
		calc->t_final = calc->t_side;
	else
		calc->t_final = calc->t_cap;
	return ((calc->t_final > 1e-3f) ? calc->t_final : -1);
}

// Calcule la normale au point d'intersection
static void	compute_hit_normal(t_ray ray, t_cylinder cy, t_calc *calc,
		t_vec3 *hitNormal)
{
	calc->hitPoint = vec3_add(ray.origin, vec3_scale(calc->d, calc->t_final));
	calc->cp = vec3_sub(calc->hitPoint, cy.center);
	calc->proj = vec3_dot(calc->cp, calc->v);
	if (fabs(calc->proj) < cy.height / 2.0f - 1e-3f)
	{
		calc->n = vec3_sub(calc->cp, vec3_scale(calc->v, calc->proj));
		*hitNormal = vec3_normalize(calc->n);
	}
	else
	{
		*hitNormal = (calc->proj > 0) ? calc->v : vec3_scale(calc->v, -1);
	}
}

// Fonction principale d'intersection du cylindre
float	intersectCylinder(t_ray ray, t_cylinder cy, t_vec3 *hitNormal)
{
	t_calc	calc;

	if (init_intersection(ray, cy, &calc) < 0)
		return (-1);
	compute_side_intersection(cy, &calc);
	compute_cap_intersection(ray, cy, &calc);
	if (select_final_intersection(&calc) < 0)
		return (-1);
	compute_hit_normal(ray, cy, &calc, hitNormal);
	return (calc.t_final);
}
