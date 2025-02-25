/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:05:49 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 19:38:13 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline int	range_is_ok(char **token_color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_atof(token_color[i]) < 0 || ft_atof(token_color[i]) > 255)
			return (0);
		i++;
	}
	return (1);
}

t_vec3	parse_color(const char *token, t_scene scene)
{
	char	**token_color;
	t_vec3	color;

	token_color = ft_split(token, ',');
	if (!check_tokens(token_color, 3) || !range_is_ok(token_color))
	{
		ft_free_array(token_color);
		ft_free_array(scene.token_if_exit);
		ft_putendl_fd("error", 2);
		ft_free_array(scene.all_file);
		close(scene.fd_if_exit);
		exit(1);
	}
	color.x = ft_atof(token_color[0]) / 255;
	color.y = ft_atof(token_color[1]) / 255;
	color.z = ft_atof(token_color[2]) / 255;
	ft_free_array(token_color);
	return (color);
}
