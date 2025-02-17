/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:29 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 21:24:12 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_camera(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.numCamera, MAX_CAMERA, 4);
	scene.token_if_exit = tokens;
	scene.camera.camPos = parse_vector(tokens[1], scene);
	scene.camera.camDir = parse_vector_normalize(tokens[2], scene);
	scene.camera.fov = ft_atof(tokens[3]);
	scene.camera.yaw = atan2f(scene.camera.camDir.x, -scene.camera.camDir.z);
	scene.camera.pitch = asinf(scene.camera.camDir.y);
	ft_free_array(tokens);
	scene.numCamera++;
	return (scene);
}
