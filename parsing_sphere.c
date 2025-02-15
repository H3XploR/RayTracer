/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:46:16 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/15 19:48:43 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_sphere(const char *line, t_scene scene)
{
	const char	**tokens = get_tokens_secure(scene, scene.numSpheres, MAX_SPHERES, 4);
	scene.token_if_exit = tokens;
	scene.spheres[scene.numSpheres].center = parse_vector(tokens[1], scene);
	scene.spheres[scene.numSpheres].radius = ft_atof(tokens[2], scene) / 2.0f;
	scene.spheres[scene.numSpheres].color = parse_color(tokens[3], scene);
	ft_free_array(tokens);
	scene.numSpheres++;
	return (scene);
}
