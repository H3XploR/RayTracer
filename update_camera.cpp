/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:27:23 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/19 17:02:04 by yantoine         ###   ########.fr       */
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
	app->scene.camera.cam_dir.x = cosf(app->scene.camera.pitch)
		* sinf(app->scene.camera.yaw);
	app->scene.camera.cam_dir.y = sinf(app->scene.camera.pitch);
	app->scene.camera.cam_dir.z = -cosf(app->scene.camera.pitch)
		* cosf(app->scene.camera.yaw);
	app->scene.camera.cam_dir = vec3_normalize(app->scene.camera.cam_dir);
	app->scene.camera.right.x = cosf(app->scene.camera.yaw);
	app->scene.camera.right.y = 0;
	app->scene.camera.right.z = sinf(app->scene.camera.yaw);
	app->scene.camera.right = vec3_normalize(app->scene.camera.right);
	app->scene.camera.up = vec3_normalize(vec3_cross(app->scene.camera.right,
				app->scene.camera.cam_dir));
}

static void	update_camera_movement(t_app *app)
{
	if (app->key_w)
		app->scene.camera.cam_pos = vec3_add(app->scene.camera.cam_pos,
				vec3_scale(app->scene.camera.cam_dir,
					app->scene.camera.move_speed));
	if (app->key_s)
		app->scene.camera.cam_pos = vec3_sub(app->scene.camera.cam_pos,
				vec3_scale(app->scene.camera.cam_dir,
					app->scene.camera.move_speed));
	if (app->key_a)
		app->scene.camera.cam_pos = vec3_sub(app->scene.camera.cam_pos,
				vec3_scale(app->scene.camera.right,
					app->scene.camera.move_speed));
	if (app->key_d)
		app->scene.camera.cam_pos = vec3_add(app->scene.camera.cam_pos,
				vec3_scale(app->scene.camera.right,
					app->scene.camera.move_speed));
}

void	update_camera(t_app *app)
{
	update_camera_rotation(app);
	update_camera_movement(app);
}
