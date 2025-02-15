/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:49:41 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/15 19:53:30 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_plane(const char *line, t_scene scene)
{
	const char	**tokens = get_tokens_secure(scene, scene.numPlanes, MAX_PLANES, 4);
	scene.token_if_exit = tokens;
	scene.planes[scene.numPlanes].point = parse_vector(tokens[1], scene);
	scene.planes[scene.numPlanes].normal = parse_vector_normalize(tokens[2], scene);
	scene.planes[scene.numPlanes].color = parse_color(tokens[3], scene);
	ft_free_array(tokens);
	scene.numPlanes++;
	return (scene);
}
