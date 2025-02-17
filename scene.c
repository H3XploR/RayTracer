/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:23:32 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 21:39:27 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	create_scene(void)
{
	t_scene	scene;

	ft_bzero(&scene, sizeof(t_scene));
	return (scene);
}
