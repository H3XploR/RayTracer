/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:28:42 by yantoine          #+#    #+#             */
/*   Updated: 2025/03/05 16:18:05 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_tokens(char **tokens, int expected)
{
	return (tokens && ft_arraylen(tokens) == expected);
}

int	check_if_max(t_scene scene, const int to_test, const int max)
{
	(void)scene;
	if (to_test >= max)
		return (0);
	return (1);
}

int	check_nb_element(t_scene scene)
{
	if (scene.num_spheres > MAX_SPHERES)
		return (0);
	if (scene.num_planes > MAX_PLANES)
		return (0);
	if (scene.num_cylinders > MAX_CYLINDERS)
		return (0);
	if (scene.num_lights > MAX_LIGHTS)
		return (0);
	if (scene.num_ambient > MAX_AMBIENT)
		return (0);
	if (scene.num_camera > MAX_CAMERA)
		return (0);
	return (1);
}
