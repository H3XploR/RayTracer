/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:27:48 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 01:13:20 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	isdigit_token(char **tokens)
{
	int	i;
	int	j;

	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			if (!ft_isdigit(tokens[i][j]) \
				&& tokens[i][j] != '\n' \
				&& tokens[i][j] != '-' \
				&& tokens[i][j] != ',')
			{
				return (0);
			}
		}
	}
	return (1);
}
