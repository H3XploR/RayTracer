/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:16:21 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 23:35:54 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_vec3(t_vec3 vec) {
    printf("(x: %.2f, y: %.2f, z: %.2f)", vec.x, vec.y, vec.z);
}

void print_ray(t_ray ray) {
    printf("Rayon d'origine : ");
    print_vec3(ray.origin);
    printf("\nDirection : ");
    print_vec3(ray.dir);
    printf("\n");
}

void print_sphere(t_sphere sphere) {
    printf("Centre : ");
    print_vec3(sphere.center);
    printf("\nRayon : %.2f", sphere.radius);
    printf("\nCouleur : ");
    print_vec3(sphere.color);
    printf("\n");
}

void print_plane(t_plane plane) {
    printf("Point : ");
    print_vec3(plane.point);
    printf("\nNormale : ");
    print_vec3(plane.normal);
    printf("\nCouleur : ");
    print_vec3(plane.color);
    printf("\n");
}

void print_cylinder(t_cylinder cyl) {
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

void print_light(t_light light) {
    printf("Position : ");
    print_vec3(light.pos);
    printf("\nIntensité : %.2f", light.brightness);
    printf("\nCouleur : ");
    print_vec3(light.color);
    printf("\n");
}

void print_ambient(t_ambient amb) {
    printf("Ratio d'ambiance : %.2f\n", amb.ratio);
    printf("Couleur ambiante : ");
    print_vec3(amb.color);
    printf("\n");
}

void print_camera(t_camera cam) {
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

void print_scene(t_scene scene) {
    int i = 0;
    
    printf("=== SCENE ===\n");
    
    // Ambiance
    printf("\n--- Ambiance ---\n");
    print_ambient(scene.ambient);
    
    // Caméra
    if (scene.numCamera > 0) {
        printf("\n--- Caméra ---\n");
        print_camera(scene.camera);
    }
    
    // Sphères
    printf("\n--- Sphères (%d) ---\n", scene.numSpheres);
    i = 0;
    while (i < scene.numSpheres) {
        printf("\nSphère %d :\n", i);
        print_sphere(scene.spheres[i]);
        i++;
    }
    
    // Plans
    printf("\n--- Plans (%d) ---\n", scene.numPlanes);
    i = 0;
    while (i < scene.numPlanes) {
        printf("\nPlan %d :\n", i);
        print_plane(scene.planes[i]);
        i++;
    }
    
    // Cylindres
    printf("\n--- Cylindres (%d) ---\n", scene.numCylinders);
    i = 0;
    while (i < scene.numCylinders) {
        printf("\nCylindre %d :\n", i);
        print_cylinder(scene.cylinders[i]);
        i++;
    }
    
    // Lumières
    printf("\n--- Lumières (%d) ---\n", scene.numLights);
    i = 0;
    while (i < scene.numLights) {
        printf("\nLumière %d :\n", i);
        print_light(scene.lights[i]);
        i++;
    }
}
