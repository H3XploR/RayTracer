/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:54:03 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 19:58:12 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_app_config(t_app *app, int argc, char **argv)
{
	if (argc > 1)
		load_config(argv[1]);
	app->win_width = WIDTH;
	app->win_height = HEIGHT;
	app->move_speed = 0.5f;
	app->rot_speed = 0.03f;
	app->mouse_sens = 0.002f;
	app->key_w = 0;
	app->key_s = 0;
	app->key_a = 0;
	app->key_d = 0;
	app->key_left = 0;
	app->key_right = 0;
	app->key_up = 0;
	app->key_down = 0;
	return (0);
}

static int	init_mlx_and_image(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
	{
		ft_putstr_fd("Erreur mlx_init\n", 2);
		return (1);
	}
	app->win = mlx_new_window(app->mlx, app->win_width * 2,
			app->win_height * 2, "Raytracer interactif");
	if (!app->win)
	{
		ft_putstr_fd("Erreur mlx_new_window\n", 2);
		return (1);
	}
	app->img = mlx_new_image(app->mlx, app->win_width, app->win_height);
	if (!app->img)
	{
		ft_putstr_fd("Erreur mlx_new_image\n", 2);
		return (1);
	}
	app->pixels = (int *)mlx_get_data_addr(app->img, &app->bpp,
			&app->size_line, &app->endian);
	if (!app->pixels)
	{
		ft_putstr_fd("Erreur mlx_get_data_addr\n", 2);
		return (1);
	}
	return (0);
}

static void	setup_hooks(t_app *app)
{
	mlx_hook(app->win, 2, 1L << 0, key_press, app);
	mlx_hook(app->win, 3, 1L << 1, key_release, app);
	mlx_hook(app->win, 6, 1L << 6, mouse_move, app);
	mlx_loop_hook(app->mlx, update_frame, app);
}

int	main(int argc, char **argv)
{
	t_app	app;

	init_app_config(&app, argc, argv);
	if (init_mlx_and_image(&app))
		return (1);
	setup_hooks(&app);
	mlx_loop(app.mlx);
	return (0);
}
