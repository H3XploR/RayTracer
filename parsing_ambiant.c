/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambiant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:04:39 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 18:56:00 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


t_scene	parsing_ambiant(const char *line, t_scene scene)
{
	const int	result_if_max = check_if_max(scene, MAX_AMBIENT);
	const char	**tokens = ft_split(line, ' ');
	const int	result_check_tokens = check_tokens(tokens, 3);

	if (!result_check_tokens)
	{
		ft_free_array(tokens);
		ft_putendl_fd("error", 2);
		close(scene.fd);
		exit(1);
	}
	scene.ambient.ambient_ratio = ft_atof(tokens[1]);
	scene.ambient.ambient_color = parse_color(tokens[2], scene);
	ft_free_array(tokens);
	return (scene);
}
