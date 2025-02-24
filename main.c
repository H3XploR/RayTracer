/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:54:03 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 00:02:01 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_app_config(t_app *app, int argc, char **argv)
{
	t_scene	scene;

	if (argc > 1)
		scene = load_config(argv[1]);
	app->win_width = WIDTH;
	app->win_height = HEIGHT;
	app->scene = scene;
	return (0);
}

static int	init_mlx_and_image(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (1);
	app->win = mlx_new_window(app->mlx, app->win_width, app->win_height,
			"Raytracer interactif");
	if (!app->win)
		return (1);
	app->img = mlx_new_image(app->mlx, app->win_width, app->win_height);
	if (!app->img)
		return (1);
	app->pixels = (int *)mlx_get_data_addr(app->img, &app->bpp, &app->size_line,
			&app->endian);
	if (!app->pixels)
		return (1);
	return (0);
}

static int	check_number(t_scene scene)
{
	if (scene.num_camera > MAX_CAMERA)
		return (0);
	if (scene.num_planes > MAX_PLANES)
		return (0);
	if (scene.num_spheres > MAX_SPHERES)
		return (0);
	if (scene.num_cylinders > MAX_CYLINDERS)
		return (0);
	if (scene.num_lights > MAX_LIGHTS)
		return (0);
	if (scene.num_ambient > MAX_AMBIENT)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	init_app_config(&app, argc, argv);
	if (!check_number(app.scene) || \
		app.scene.num_camera == 0 \
		|| init_mlx_and_image(&app))
		return (1);
	update_camera(&app);
	render_scene(&app);
	mlx_hook(app.win, 2, 1L << 0, key_press, &app);
	mlx_hook(app.win, 17, 0, handle_close, &app);
	mlx_loop(app.mlx);
	return (0);
}
