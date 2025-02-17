/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:27:23 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 19:30:13 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_camera_rotation(t_app *app)
{
	if (app->key_left)
		app->yaw -= app->rot_speed;
	if (app->key_right)
		app->yaw += app->rot_speed;
	if (app->key_up)
		app->pitch += app->rot_speed;
	if (app->key_down)
		app->pitch -= app->rot_speed;
	if (app->pitch > 1.57f - 0.01f)
		app->pitch = 1.57f - 0.01f;
	if (app->pitch < -1.57f + 0.01f)
		app->pitch = -1.57f + 0.01f;
	app->cam_dir.x = cosf(app->pitch) * sinf(app->yaw);
	app->cam_dir.y = sinf(app->pitch);
	app->cam_dir.z = -cosf(app->pitch) * cosf(app->yaw);
	app->cam_dir = vec3_normalize(app->cam_dir);
	app->right = (t_vec3){cosf(app->yaw), 0, sinf(app->yaw)};
	app->right = vec3_normalize(app->right);
	app->cam_up = vec3_normalize(vec3_cross(app->right, app->cam_dir));
}

static void	update_camera_movement(t_app *app)
{
	if (app->key_w)
		app->cam_pos = vec3_add(app->cam_pos,
				vec3_scale(app->cam_dir, app->move_speed));
	if (app->key_s)
		app->cam_pos = vec3_sub(app->cam_pos,
				vec3_scale(app->cam_dir, app->move_speed));
	if (app->key_a)
		app->cam_pos = vec3_sub(app->cam_pos,
				vec3_scale(app->right, app->move_speed));
	if (app->key_d)
		app->cam_pos = vec3_add(app->cam_pos,
				vec3_scale(app->right, app->move_speed));
}

void	update_camera(t_app *app)
{
	update_camera_rotation(app);
	update_camera_movement(app);
}
