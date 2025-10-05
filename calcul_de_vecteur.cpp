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
	t_vec3 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

t_vec3	vec3_scale(t_vec3 a, float s)
{
	t_vec3 result;
	result.x = a.x * s;
	result.y = a.y * s;
	result.z = a.z * s;
	return result;
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}
