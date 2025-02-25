/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peripherique.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:22:27 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 19:06:52 by yantoine         ###   ########.fr       */
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
		free(app->scene.all_file);
		exit(0);
	}
	return (0);
}

int	handle_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	mlx_destroy_image(app->mlx, app->img);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	ft_free_array(app->scene.all_file);
	free(app->scene.all_file);
	free(app->mlx);
	exit(0);
	return (0);
}
