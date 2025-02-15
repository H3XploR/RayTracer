/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambiant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:04:39 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 20:52:08 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


t_scene	parsing_ambiant(const char *line, t_scene scene)
{
	const char **tokens = get_tokens_secure(scene, scene.numAmbient, MAX_AMBIENT, 3);
	scene.token_if_exit = tokens;
	scene.ambient.ambient_ratio = ft_atof(tokens[1]);
	scene.ambient.ambient_color = parse_color(tokens[2], scene);
	ft_free_array(tokens);
	scene.numAmbient++;
	return (scene);
}
