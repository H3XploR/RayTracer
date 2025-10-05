/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:41:15 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/18 20:41:16 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Fonction principale d'intersection du cylindre
float	intersect_cylinder(t_ray ray, t_cylinder cy, t_vec3 *hitNormal)
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
