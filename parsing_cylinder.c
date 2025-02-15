/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:54:13 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/15 19:54:28 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
