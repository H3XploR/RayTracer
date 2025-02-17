/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:27:23 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 23:07:57 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_camera_rotation(t_app *app)
{
	if (app->key_left)
		app->scene.camera.yaw -= app->scene.camera.rot_speed;
	if (app->key_right)
		app->scene.camera.yaw += app->scene.camera.rot_speed;
	if (app->key_up)
		app->scene.camera.pitch += app->scene.camera.rot_speed;
	if (app->key_down)
		app->scene.camera.pitch -= app->scene.camera.rot_speed;
	if (app->scene.camera.pitch > 1.57f - 0.01f)
		app->scene.camera.pitch = 1.57f - 0.01f;
	if (app->scene.camera.pitch < -1.57f + 0.01f)
		app->scene.camera.pitch = -1.57f + 0.01f;
	app->scene.camera.camDir.x = cosf(app->scene.camera.pitch) * sinf(app->scene.camera.yaw);
	app->scene.camera.camDir.y = sinf(app->scene.camera.pitch);
	app->scene.camera.camDir.z = -cosf(app->scene.camera.pitch) * cosf(app->scene.camera.yaw);
	app->scene.camera.camDir = vec3_normalize(app->scene.camera.camDir);
	app->scene.camera.right = (t_vec3){cosf(app->scene.camera.yaw), 0, sinf(app->scene.camera.yaw)};
	app->scene.camera.right = vec3_normalize(app->scene.camera.right);
	app->scene.camera.up = vec3_normalize(vec3_cross(app->scene.camera.right, app->scene.camera.camDir));
}

static void	update_camera_movement(t_app *app)
{
	if (app->key_w)
		app->scene.camera.camPos = vec3_add(app->scene.camera.camPos,
				vec3_scale(app->scene.camera.camDir, app->scene.camera.move_speed));
	if (app->key_s)
		app->scene.camera.camPos = vec3_sub(app->scene.camera.camPos,
				vec3_scale(app->scene.camera.camDir, app->scene.camera.move_speed));
	if (app->key_a)
		app->scene.camera.camPos = vec3_sub(app->scene.camera.camPos,
				vec3_scale(app->scene.camera.right, app->scene.camera.move_speed));
	if (app->key_d)
		app->scene.camera.camPos = vec3_add(app->scene.camera.camPos,
				vec3_scale(app->scene.camera.right, app->scene.camera.move_speed));
}

void	update_camera(t_app *app)
{
	update_camera_rotation(app);
	update_camera_movement(app);
}
