/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:30:45 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 22:55:22 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	update_frame(t_app *app)
{
	update_camera(app);
	render_scene(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (0);
}
