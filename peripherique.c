/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peripherique.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:22:27 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/24 17:01:54 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_press(int keycode, t_app *app)
{
	(void)app;
	printf("keycode: %d\n", keycode);
	if (keycode == 53 || keycode == 65307)
		exit(0);
	return (0);
}

int	handle_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}
