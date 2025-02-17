/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambiant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:04:39 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 21:53:34 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


t_scene	parsing_ambiant(t_scene scene)
{
	char **tokens;

	tokens = get_tokens_secure(scene, scene.numAmbient, MAX_AMBIENT, 3);
	scene.token_if_exit = tokens;
	scene.ambient.ratio = ft_atof(tokens[1]);
	scene.ambient.color = parse_color(tokens[2], scene);
	ft_free_array(tokens);
	scene.numAmbient++;
	return (scene);
}
