/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_de_vecteur.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:15:13 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/13 21:08:51 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// ----- Opérations sur les vecteurs

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3_scale(t_vec3 a, float s)
{
	return ((t_vec3){a.x * s, a.y * s, a.z * s});
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x});
}
