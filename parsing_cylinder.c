/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:54:13 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/18 17:24:08 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_cylindre(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.numCylinders, MAX_CYLINDERS, 6);
	scene.token_if_exit = tokens;
	scene.cylinders[scene.numCylinders].center = parse_vector(tokens[1], scene);
	scene.cylinders[scene.numCylinders].axis = parse_vector_normalize(tokens[2],
			scene);
	scene.cylinders[scene.numCylinders].radius = ft_atof(tokens[3]);
	scene.cylinders[scene.numCylinders].height = ft_atof(tokens[4]);
	scene.cylinders[scene.numCylinders].color = parse_color(tokens[5], scene);
	ft_free_array(tokens);
	scene.numCylinders++;
	return (scene);
}
