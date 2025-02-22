/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:24:30 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/19 16:59:45 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	render_pixel(t_app *app, int x, int y)
{
	t_calc			calc;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	calc.ndc_x = (x + 0.5f) / app->win_width;
	calc.ndc_y = (y + 0.5f) / app->win_height;
	calc.aspect = (float)app->win_width / app->win_height;
	calc.scale = tanf((app->scene.camera.fov * 0.5f) * (M_PI / 180.0f));
	calc.screen_x = (2 * calc.ndc_x - 1) * calc.aspect * calc.scale;
	calc.screen_y = (1 - 2 * calc.ndc_y) * calc.scale;
	calc.ray_dir = vec3_add(app->scene.camera.cam_dir,
			vec3_add(vec3_scale(app->scene.camera.right, calc.screen_x),
				vec3_scale(app->scene.camera.up, calc.screen_y)));
	calc.ray_dir = vec3_normalize(calc.ray_dir);
	calc.ray.origin = app->scene.camera.cam_pos;
	calc.ray.dir = calc.ray_dir;
	calc.color = trace(calc.ray, app->scene);
	r = (unsigned char)(fminf(calc.color.x, 1.0f) * 255);
	g = (unsigned char)(fminf(calc.color.y, 1.0f) * 255);
	b = (unsigned char)(fminf(calc.color.z, 1.0f) * 255);
	app->pixels[y * app->win_width
		+ x] = (255 << 24) | (r << 16) | (g << 8) | b;
}

void	render_scene(t_app *app)
{
	const int	total_pixels = app->win_height * app->win_width;
	static int	done;
	static int		progress;
	int		y;
	int		x;
	

	y = 0;
	while (y < app->win_height)
	{
		x = 0;
		while (x < app->win_width)
		{
			progress = ((y * app->win_width + x + 1) * 100) / total_pixels;
			render_pixel(app, x, y);
			x++;
			if (!done)
				printf("\rChargement de l'écran : %d%%  ", progress);
			else
				printf("\rTERMINE 				");
			if (progress >= 100)
				done = 1;
		}
		y++;
	}
}
