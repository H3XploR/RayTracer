/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peripherique.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:22:27 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 00:15:35 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_press(int keycode, t_app *app)
{
	(void)app;
	printf("keycode: %d\n", keycode);
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_image(app->mlx, app->img);
		mlx_destroy_window(app->mlx, app->win);
		mlx_destroy_display(app->mlx);
		free(app->mlx);
		exit(0);
	}
	return (0);
}

int	handle_close(void *param)
{
	t_app *app;

	app = (t_app *)param;
	mlx_destroy_image(app->mlx, app->img);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	exit(0);
	return (0);
}
