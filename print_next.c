/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:02:32 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/18 17:02:42 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_vec3(t_vec3 vec)
{
	printf("(x: %.2f, y: %.2f, z: %.2f)", vec.x, vec.y, vec.z);
}

void	print_ray(t_ray ray)
{
	printf("Rayon d'origine : ");
	print_vec3(ray.origin);
	printf("\nDirection : ");
	print_vec3(ray.dir);
	printf("\n");
}

void	print_sphere(t_sphere sphere)
{
	printf("Centre : ");
	print_vec3(sphere.center);
	printf("\nRayon : %.2f", sphere.radius);
	printf("\nCouleur : ");
	print_vec3(sphere.color);
	printf("\n");
}

void	print_plane(t_plane plane)
{
	printf("Point : ");
	print_vec3(plane.point);
	printf("\nNormale : ");
	print_vec3(plane.normal);
	printf("\nCouleur : ");
	print_vec3(plane.color);
	printf("\n");
}

void	print_cylinder(t_cylinder cyl)
{
	printf("Centre : ");
	print_vec3(cyl.center);
	printf("\nAxe : ");
	print_vec3(cyl.axis);
	printf("\nRayon : %.2f", cyl.radius);
	printf("\nHauteur : %.2f", cyl.height);
	printf("\nCouleur : ");
	print_vec3(cyl.color);
	printf("\n");
}

