/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:49:41 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 21:30:47 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_plane(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.numPlanes, MAX_PLANES, 4);
	scene.token_if_exit = tokens;
	scene.planes[scene.numPlanes].point = parse_vector(tokens[1], scene);
	scene.planes[scene.numPlanes].normal = parse_vector_normalize(tokens[2], scene);
	scene.planes[scene.numPlanes].color = parse_color(tokens[3], scene);
	ft_free_array(tokens);
	scene.numPlanes++;
	return (scene);
}

float	intersectPlane(t_ray ray, t_plane p, t_vec3 *hitNormal)
{
	float	denom;
	float	t;

	denom = vec3_dot(p.normal, ray.dir);
	if (fabs(denom) < 1e-6f)
		return (-1);
	t = vec3_dot(vec3_sub(p.point, ray.origin), p.normal) / denom;
	if (t < 1e-3f)
		return (-1);
	*hitNormal = p.normal;
	return (t);
}

