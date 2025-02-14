/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 01:41:17 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/14 01:50:00 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// ----- Parsing du fichier de configuration -----
int	load_config(const char *filename)
{
	int	fd;
	char	line[256];
	float	ratio;

	fd = open(filename, "r");
	if (!fd)
	{
		printf("Erreur : impossible d'ouvrir %s\n", filename);
		return ;
	}
	return (fd);
}
