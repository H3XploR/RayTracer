/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peripherique.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:22:27 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 22:55:44 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_press(int keycode, t_app *app)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		app->key_w = 1;
	if (keycode == 1)
		app->key_s = 1;
	if (keycode == 0)
		app->key_a = 1;
	if (keycode == 2)
		app->key_d = 1;
	if (keycode == 123)
		app->key_left = 1;
	if (keycode == 124)
		app->key_right = 1;
	if (keycode == 126)
		app->key_up = 1;
	if (keycode == 125)
		app->key_down = 1;
	return (0);
}

int	key_release(int keycode, t_app *app)
{
	if (keycode == 13)
		app->key_w = 0;
	if (keycode == 1)
		app->key_s = 0;
	if (keycode == 0)
		app->key_a = 0;
	if (keycode == 2)
		app->key_d = 0;
	if (keycode == 123)
		app->key_left = 0;
	if (keycode == 124)
		app->key_right = 0;
	if (keycode == 126)
		app->key_up = 0;
	if (keycode == 125)
		app->key_down = 0;
	return (0);
}

int	mouse_move(int x, int y, t_app *app)
{
	static int	last_x = -1;
	static int	last_y = -1;
	int			dx;
	int			dy;

	if (last_x == -1 || last_y == -1)
	{
		last_x = x;
		last_y = y;
		return (0);
	}
	dx = x - last_x;
	dy = y - last_y;
	app->scene.camera.yaw += dx * app->mouse_sens;
	app->scene.camera.pitch -= dy * app->mouse_sens;
	last_x = x;
	last_y = y;
	return (0);
}

