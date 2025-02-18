/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:16:21 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/18 17:03:05 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_light(t_light light)
{
	printf("Position : ");
	print_vec3(light.pos);
	printf("\nIntensité : %.2f", light.brightness);
	printf("\nCouleur : ");
	print_vec3(light.color);
	printf("\n");
}

void	print_ambient(t_ambient amb)
{
	printf("Ratio d'ambiance : %.2f\n", amb.ratio);
	printf("Couleur ambiante : ");
	print_vec3(amb.color);
	printf("\n");
}

void	print_camera(t_camera cam)
{
	printf("Position de la caméra : ");
	print_vec3(cam.camPos);
	printf("\nDirection : ");
	print_vec3(cam.camDir);
	printf("\nRight : ");
	print_vec3(cam.right);
	printf("\nUp : ");
	print_vec3(cam.up);
	printf("\nFOV : %.2f", cam.fov);
	printf("\nYaw : %.2f", cam.yaw);
	printf("\nPitch : %.2f", cam.pitch);
	printf("\n");
}

void	print_scene(t_scene scene)
{
	int	i;

	i = 0;
	printf("=== SCENE ===\n");
	printf("\n--- Ambiance ---\n");
	print_ambient(scene.ambient);
	if (scene.numCamera > 0)
	{
		printf("\n--- Caméra ---\n");
		print_camera(scene.camera);
	}
	printf("\n--- Sphères (%d) ---\n", scene.numSpheres);
	i = 0;
	while (i < scene.numSpheres)
	{
		printf("\nSphère %d :\n", i);
		print_sphere(scene.spheres[i]);
		i++;
	}
	printf("\n--- Plans (%d) ---\n", scene.numPlanes);
	i = 0;
	while (i < scene.numPlanes)
	{
		printf("\nPlan %d :\n", i);
		print_plane(scene.planes[i]);
		i++;
	}
	printf("\n--- Cylindres (%d) ---\n", scene.numCylinders);
	i = 0;
	while (i < scene.numCylinders)
	{
		printf("\nCylindre %d :\n", i);
		print_cylinder(scene.cylinders[i]);
		i++;
	}
	printf("\n--- Lumières (%d) ---\n", scene.numLights);
	i = 0;
	while (i < scene.numLights)
	{
		printf("\nLumière %d :\n", i);
		print_light(scene.lights[i]);
		i++;
	}
}
