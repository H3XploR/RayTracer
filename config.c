/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 01:41:17 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 19:36:04 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline t_scene	parsing_line(char *line, t_scene scene)
{
	scene.line_if_exit = line;
	if (line[0] == '#' || line[0] == '\n')
		return (scene);
	else if (line[0] == 'A')
		scene = parsing_ambiant(scene);
	else if (line[0] == 'C')
		scene = parsing_camera(scene);
	else if (line[0] == 'L')
		scene = parsing_light(scene);
	else if (ft_strncmp(line, "sp", 2) == 0)
		scene = parsing_sphere(scene);
	else if (ft_strncmp(line, "pl", 2) == 0)
		scene = parsing_plane(scene);
	else if (ft_strncmp(line, "cy", 2) == 0)
		scene = parsing_cylindre(scene);
	else
		printf("Erreur : ligne non reconnue\n");
	return (scene);
}

static char	**get_all_file(int fd)
{
	char	*join;
	char	*line;
	char	*data;
	char	**splited;
	int		first;

	first = 1;
	line = NULL;
	data = ft_calloc(1, 1);
	while (1)
	{
		if (!first)
			data = join;
		line = get_next_line(fd);
		if (!line)
			break ;
		join = ft_strjoin(data, line);
		free(line);
		free(data);
		first = 0;
	}
	splited = ft_split(join, '\n');
	free(data);
	return (splited);
}

// ----- Parsing du fichier de configuration -----
t_scene	load_config(const char *filename)
{
	int		fd;
	int		i;
	char	*line;
	t_scene	scene;

	scene = create_scene();
	fd = open(filename, O_RDONLY);
	if (fd <= 0 || !have_extension(filename))
	{
		printf("Erreur : impossible d'ouvrir %s\n", filename);
		return (scene);
	}
	scene.fd_if_exit = fd;
	scene.all_file = get_all_file(fd);
	i = -1;
	while (scene.all_file[++i])
	{
		line = scene.all_file[i];
		if (!line)
			break ;
		scene = parsing_line(line, scene);
	}
	ft_free_array(scene.all_file);
	return (scene);
}
