/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:54:13 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/19 16:53:04 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_cylindre(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.num_cylinders, MAX_CYLINDERS, 6);
	scene.token_if_exit = tokens;
	scene.cylinders[scene.num_cylinders].center = \
		parse_vector(tokens[1], scene);
	scene.cylinders[scene.num_cylinders].axis = \
		parse_vector_normalize(tokens[2],
			scene);
	scene.cylinders[scene.num_cylinders].radius = ft_atof(tokens[3]);
	scene.cylinders[scene.num_cylinders].height = ft_atof(tokens[4]);
	scene.cylinders[scene.num_cylinders].color = parse_color(tokens[5], scene);
	ft_free_array(tokens);
	scene.num_cylinders++;
	return (scene);
}
