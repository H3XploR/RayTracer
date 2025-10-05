/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_de_vecteur2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:59:38 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/13 21:08:27 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vec3_length(t_vec3 a)
{
	return (sqrtf(vec3_dot(a, a)));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	float	len;

	len = vec3_length(a);
	if (len > 0)
		return (vec3_scale(a, 1.0f / len));
	return (a);
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	t_vec3 result;
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return result;
}
