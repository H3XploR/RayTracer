/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 01:41:17 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/15 19:56:05 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline t_scene	parsing_line(const char *line, t_scene scene)
{
	scene->line_if_exit = line;
	if (line[0] == '#')
		return ;
	else if (line[0] == 'A')
		parsing_ambiant(line, scene);
	else if (line[0] == 'C')
		parsing_camera(line, scene);
	else if (line[0] == 'L')
		parsing_light(line, scene);
	else if (ft_strncmp(line, "sp", 2) == 0)
		parsing_sphere(line, scene);
	else if (ft_strncmp(line, "pl", 2) == 0)
		parsing_plane(line, scene);
	else if (ft_strncmp(line, "cy", 2) == 0)
		parsing_cylindre(line, scene);
	else
		printf("Erreur : ligne non reconnue\n");
}

// ----- Parsing du fichier de configuration -----
t_scene	load_config(const char *filename)
{
	int			fd;
	char		line[256];
	const char		*line;
	t_scene		scene;

	scene = create_scene(void);
	fd = open(filename, "r");
	if (!fd)
	{
		printf("Erreur : impossible d'ouvrir %s\n", filename);
		return ;
	}
	scene.fd_if_exit = fd;
	while (1)
	{
		line = (const char *)get_next_line(fd);
		if (!line)
			break ;
		free(line);
		parsing_line(line, scene);
	}
	return (scene);
}
