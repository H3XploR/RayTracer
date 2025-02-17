/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:39:08 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 21:29:55 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_light(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.numLights, MAX_LIGHTS, 4);
	scene.token_if_exit = tokens;
	scene.lights[scene.numLights].pos = parse_vector(tokens[1], scene);
	scene.lights[scene.numLights].brightness = ft_atof(tokens[2]);
	scene.lights[scene.numLights].color = parse_color(tokens[3], scene);
	ft_free_array(tokens);
	scene.numLights++;
	return (scene);
}
