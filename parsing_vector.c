/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:16:01 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 19:37:48 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline int	range_is_ok(char **token_vector)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_atof(token_vector[i]) < -FLT_MAX
			|| ft_atof(token_vector[i]) > FLT_MAX)
			return (0);
		i++;
	}
	return (1);
}

t_vec3	parse_vector(const char *token, t_scene scene)
{
	char	**token_vector;
	t_vec3	vector;

	token_vector = ft_split(token, ',');
	if (!check_tokens(token_vector, 3) || !range_is_ok(token_vector))
	{
		ft_free_array(token_vector);
		ft_free_array(scene.token_if_exit);
		ft_putendl_fd("error", 2);
		ft_free_array(scene.all_file);
		close(scene.fd_if_exit);
		exit(1);
	}
	vector.x = ft_atof(token_vector[0]);
	vector.y = ft_atof(token_vector[1]);
	vector.z = ft_atof(token_vector[2]);
	ft_free_array(token_vector);
	return (vector);
}

t_vec3	parse_vector_normalize(const char *token, t_scene scene)
{
	t_vec3	vector;

	vector = parse_vector(token, scene);
	vector = vec3_normalize(vector);
	return (vector);
}
