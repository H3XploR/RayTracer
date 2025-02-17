/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:07:07 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/17 19:10:35 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#include "miniRT.h"

// Renvoie true si le rayon intersecte un objet, et met à jour tMin, hitNormal et objColor
bool intersectObjects(Ray ray, float *tMin, t_vec3 *hitNormal, t_vec3 *objColor) {
    bool hit = false;
    float t;
    t_vec3 n;
    int i = 0;
    while (i < numSpheres) {
        t = intersectSphere(ray, spheres[i], &n);
        if (t > 1e-3f && t < *tMin) { *tMin = t; *hitNormal = n; *objColor = spheres[i].color; hit = true; }
        i++;
    }
    i = 0;
    while (i < numPlanes) {
        t = intersectPlane(ray, planes[i], &n);
        if (t > 1e-3f && t < *tMin) { *tMin = t; *hitNormal = n; *objColor = planes[i].color; hit = true; }
        i++;
    }
    i = 0;
    while (i < numCylinders) {
        t = intersectCylinder(ray, cylinders[i], &n);
        if (t > 1e-3f && t < *tMin) { *tMin = t; *hitNormal = n; *objColor = cylinders[i].color; hit = true; }
        i++;
    }
    return hit;
}

// Calcule l'éclairage (ambiant, diffus et spéculaire) sur un point d'impact
t_vec3 calcLighting(t_vec3 hitPoint, t_vec3 hitNormal, t_vec3 objColor) {
    t_vec3 color = vec3_scale(objColor, ambient_ratio);
    int i = 0;
    while (i < numLights) {
        Light light = lights[i];
        t_vec3 L = vec3_normalize(vec3_sub(light.pos, hitPoint));
        if (!isInShadow(hitPoint, light.pos)) {
            float diff = fmaxf(0.0f, vec3_dot(hitNormal, L));
            t_vec3 viewDir = vec3_normalize(vec3_sub(camPos, hitPoint));
            t_vec3 halfDir = vec3_normalize(vec3_add(L, viewDir));
            float spec = powf(fmaxf(0.0f, vec3_dot(hitNormal, halfDir)), 32.0f);
            color = vec3_add(color, vec3_scale(vec3_mul(objColor, light.color),
                                        diff * light.brightness));
            color = vec3_add(color, vec3_scale((t_vec3){1, 1, 1},
                                        spec * light.brightness));
        }
        i++;
    }
    if (color.x > 1.0f) color.x = 1.0f;
    if (color.y > 1.0f) color.y = 1.0f;
    if (color.z > 1.0f) color.z = 1.0f;
    return color;
}

// Fonction principale de lancer de rayon (trace)
t_vec3 trace(Ray ray) {
    float tMin = 1e9;
    t_vec3 hitNormal = {0, 0, 0};
    t_vec3 objColor = {0, 0, 0};
    if (intersectObjects(ray, &tMin, &hitNormal, &objColor)) {
        t_vec3 hitPoint = vec3_add(ray.origin, vec3_scale(ray.dir, tMin));
        return calcLighting(hitPoint, hitNormal, objColor);
    }
    return (t_vec3){0.2f, 0.7f, 1.0f}; // Couleur de fond (ciel)
}

