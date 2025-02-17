/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:58:42 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 19:03:01 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Vérifie les intersections avec les sphères
static bool checkShadowSphere(const Ray shadowRay, float maxT, float epsilon) {
    int i = 0;
    t_vec3 dummy;
    float t;
    while (i < numSpheres) {
        t = intersectSphere(shadowRay, spheres[i], &dummy);
        if (t > epsilon && t < maxT)
            return true;
        i++;
    }
    return false;
}

// Vérifie les intersections avec les plans
static bool checkShadowPlane(const Ray shadowRay, float maxT, float epsilon) {
    int i = 0;
    t_vec3 dummy;
    float t;
    while (i < numPlanes) {
        t = intersectPlane(shadowRay, planes[i], &dummy);
        if (t > epsilon && t < maxT)
            return true;
        i++;
    }
    return false;
}

// Vérifie les intersections avec les cylindres
static bool checkShadowCylinder(const Ray shadowRay, float maxT, float epsilon) {
    int i = 0;
    t_vec3 dummy;
    float t;
    while (i < numCylinders) {
        t = intersectCylinder(shadowRay, cylinders[i], &dummy);
        if (t > epsilon && t < maxT)
            return true;
        i++;
    }
    return false;
}

// Fonction principale qui détermine si le point est dans l'ombre
bool isInShadow(t_vec3 hitPoint, t_vec3 lightPos) {
    const float epsilon = 1e-3f;
    t_vec3 toLight = vec3_sub(lightPos, hitPoint);
    float maxT = vec3_length(toLight);
    t_vec3 L = vec3_normalize(toLight);
    Ray shadowRay;
    shadowRay.origin = vec3_add(hitPoint, vec3_scale(L, epsilon));
    shadowRay.direction = L;

    if (checkShadowSphere(shadowRay, maxT, epsilon))
        return true;
    if (checkShadowPlane(shadowRay, maxT, epsilon))
        return true;
    if (checkShadowCylinder(shadowRay, maxT, epsilon))
        return true;
    
    return false;
}

