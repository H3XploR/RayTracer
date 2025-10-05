/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:49:41 by yantoine          #+#    #+#             */
/*   Updated: 2025/03/05 14:24:37 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_plane(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.num_planes, MAX_PLANES, 4);
	scene.token_if_exit = tokens;
	scene.planes[scene.num_planes].point = parse_vector(tokens[1], scene);
	scene.planes[scene.num_planes].normal = parse_vector_normalize(tokens[2],
			scene);
	scene.planes[scene.num_planes].color = parse_color(tokens[3], scene);
	ft_free_array(tokens);
	scene.num_planes++;
	return (scene);
}

float	intersect_plane(t_ray ray, t_plane p, t_vec3 *hitNormal)
{
	float	denom;
	float	t;

	denom = vec3_dot(p.normal, ray.dir);
	if (fabs(denom) < 0.000001f)
		return (-1);
	t = vec3_dot(vec3_sub(p.point, ray.origin), p.normal) / denom;
	if (t < 0.001f)
		return (-1);
	*hitNormal = p.normal;
	return (t);
}
