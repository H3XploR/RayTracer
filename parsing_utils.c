/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:23:21 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 02:46:24 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	**get_tokens_secure(t_scene scene, const int numObject,
		const int numObjectMax, const int supposed_nb_token)
{
	char	**tokens;

	check_if_max(scene, numObject, numObjectMax);
	tokens = ft_split(scene.line_if_exit, ' ');
	if (!check_tokens(tokens, supposed_nb_token) || !isdigit_token(tokens + 1))
	{
		ft_free_array(tokens);
		ft_putendl_fd("error", 2);
		free(scene.line_if_exit);
		close(scene.fd_if_exit);
		exit(1);
	}
	return (tokens);
}
