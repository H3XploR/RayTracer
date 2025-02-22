/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_extension.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:45:59 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/22 21:04:31 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	have_extension(const char *line)
{
	const int	lenght = ft_strlen(line);

	if (lenght < 3)
		return (0);
	if (ft_strncmp(lenght + line - 3, ".rt", lenght) == 0)
		return (1);
	printf("erreur: pas d'extension\n");
	return (0);
}
