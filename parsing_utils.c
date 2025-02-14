/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:23:21 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 20:48:49 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


inline	char	**get_tokens_secure(t_scene scene, const int numObject, const int numObjectMax, const int supposed_nb_token)
{
	const int	result_if_max = check_if_max(scene, numObject, numObjectMax);
	const char	**tokens = ft_split(scene.line_if_exit, ' ');
	const int	result_check_tokens = check_tokens(tokens, supposed_nb_token);

	if (!result_check_tokens)
	{
		ft_free_array(tokens);
		ft_putendl_fd("error", 2);
		free(scene.line_if_exit);
		close(scene.fd);
		exit(1);
	}
	return (tokens);
}
