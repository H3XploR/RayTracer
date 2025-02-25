/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:28:42 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 01:44:31 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_tokens(char **tokens, int expected)
{
	return (tokens && ft_arraylen(tokens) == expected);
}

int	check_if_max(t_scene scene, const int to_test, const int max)
{
	(void)scene;
	if (to_test >= max)
		return (0);
	return (1);
}
