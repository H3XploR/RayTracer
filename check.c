/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:28:42 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 20:15:29 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline int	check_tokens(char **tokens, int expected)
{
	return (tokens && ft_arraylen(tokens) == expected);
}

inline void check_if_max(t_scene scene, const int to_test, const int max)
{
	if (to_test >= max)
	{
		printf("error:\n");
		close(scene.fd_if_exit);
		free(scene->line_if_exit);
		exit(1);
	}
}
