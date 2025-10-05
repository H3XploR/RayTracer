/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:29 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/19 16:58:31 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	parsing_camera(t_scene scene)
{
	char	**tokens;

	tokens = get_tokens_secure(scene, scene.num_camera, MAX_CAMERA, 4);
	scene.token_if_exit = tokens;
	scene.camera.cam_pos = parse_vector(tokens[1], scene);
	scene.camera.cam_dir = parse_vector_normalize(tokens[2], scene);
	scene.camera.fov = ft_atof(tokens[3]);
	scene.camera.yaw = atan2f(scene.camera.cam_dir.x, -scene.camera.cam_dir.z);
	scene.camera.pitch = asinf(scene.camera.cam_dir.y);
	ft_free_array(tokens);
	scene.num_camera++;
	return (scene);
}
