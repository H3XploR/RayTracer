/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:39:08 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/19 16:49:57 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_light(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.num_lights, MAX_LIGHTS, 4);
	scene.token_if_exit = tokens;
	scene.lights[scene.num_lights].pos = parse_vector(tokens[1], scene);
	scene.lights[scene.num_lights].brightness = ft_atof(tokens[2]);
	scene.lights[scene.num_lights].color = parse_color(tokens[3], scene);
	ft_free_array(tokens);
	scene.num_lights++;
	return (scene);
}
