/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 01:41:17 by yantoine          #+#    #+#             */
/*   Updated: 2025/03/17 16:03:35 by yantoine         ###   ########.fr       */
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

static t_calc	init_calc(void)
{
	t_calc	init;

	init.count = 0;
	init.line = NULL;
	init.data = ft_calloc(1, 1);
	return (init);
}

static char	**get_all_file(int fd)
{
	t_calc	calc;

	calc = init_calc();
	while (1)
	{
		if (calc.count > MAX_SPHERES + MAX_PLANES \
			+ MAX_CYLINDERS + MAX_LIGHTS + MAX_AMBIENT + MAX_CAMERA)
		{
			free(calc.join);
			ft_putstr_fd("Erreur:\n max element reached\n", 2);
			close(fd);
			exit(1);
		}
		if (calc.count != 0)
			calc.data = calc.join;
		calc.line = get_next_line(fd);
		if (!calc.line)
			break ;
		calc.join = ft_strjoin(calc.data, calc.line);
		free(calc.line);
		free(calc.data);
		calc.count++;
	}
	calc.splited = ft_split(calc.join, '\n');
	return (free(calc.data), calc.splited);
}

static t_scene	initialisation(int fd, const char *filename)
{
	t_scene	scene;

	scene = create_scene();
	if (fd <= 0 || !have_extension(filename))
	{
		printf("Erreur : impossible d'ouvrir %s\n", filename);
		scene.no = 1;
		return (scene);
	}
	scene.fd_if_exit = fd;
	return (scene);
}

// ----- Parsing du fichier de configuration -----
t_scene	load_config(const char *filename)
{
	int		fd;
	int		i;
	char	*line;
	t_scene	scene;

	fd = open(filename, O_RDONLY);
	scene = initialisation(fd, filename);
	if (scene.no == 1)
		return (scene);
	scene.all_file = get_all_file(fd);
	i = -1;
	while (scene.all_file[++i])
	{
		line = scene.all_file[i];
		if (!line)
			break ;
		if (!check_nb_element(scene))
		{
			ft_free_array(scene.all_file);
			ft_putstr_fd("Error\n Bad number element\n", 1);
			exit(1);
		}
		scene = parsing_line(line, scene);
	}
	return (ft_free_array(scene.all_file), scene);
}
