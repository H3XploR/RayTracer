/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:05:49 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 20:25:45 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	parse_color(const char *token, t_scene scene)
{
	const char	**token_color = ft_split(token, ',');
	t_color		color;

	if (!check_tokens(token_color, 3))
	{
		ft_free_array(tokens_color);
		ft_free_array(scene.token_if_exit);
		ft_putendl_fd("error", 2);
		free(scene.line_if_exit);
		close(scene.fd);
		exit(1);
	}
	color.r = ft_atoi(token_color[0]) / 255;
	color.g = ft_atoi(token_color[1]) / 255;
	color.b = ft_atoi(token_color[2]) / 255;
}
