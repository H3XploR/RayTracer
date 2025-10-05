/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:07:07 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/19 16:59:53 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	clamp_color(t_vec3 color)
{
	if (color.x > 1.0f)
		color.x = 1.0f;
	if (color.y > 1.0f)
		color.y = 1.0f;
	if (color.z > 1.0f)
		color.z = 1.0f;
	return (color);
}

static t_vec3	calc_light_contribution(t_hit_info hit, t_light light,
		t_camera camera, t_scene scene)
{
	t_vec3	l;
	float	diff;
	t_vec3	view_dir;
	t_vec3	half_dir;
	float	spec;
	t_vec3	zero_vec;
	t_vec3	white_vec;

	zero_vec.x = 0; zero_vec.y = 0; zero_vec.z = 0;
	white_vec.x = 1; white_vec.y = 1; white_vec.z = 1;
	l = vec3_normalize(vec3_sub(light.pos, hit.point));
	if (is_in_shadow(hit.point, light.pos, scene))
		return (zero_vec);
	diff = fmaxf(0.0f, vec3_dot(hit.normal, l));
	view_dir = vec3_normalize(vec3_sub(camera.cam_pos, hit.point));
	half_dir = vec3_normalize(vec3_add(l, view_dir));
	spec = powf(fmaxf(0.0f, vec3_dot(hit.normal, half_dir)), 32.0f);
	return (vec3_add(vec3_scale(vec3_mul(hit.color, \
			light.color), diff * light.brightness), \
			vec3_scale(white_vec, \
			spec * light.brightness)));
}

t_vec3	calc_lighting(t_vec3 hit_point, t_vec3 hit_normal, t_vec3 obj_color,
		t_scene scene)
{
	t_vec3		color;
	t_hit_info	hit;
	int			i;

	color = vec3_scale(obj_color, scene.ambient.ratio);
	hit.point = hit_point;
	hit.normal = hit_normal;
	hit.color = obj_color;
	i = 0;
	while (i < scene.num_lights)
	{
		color = vec3_add(color, calc_light_contribution(hit, scene.lights[i],
					scene.camera, scene));
		i++;
	}
	return (clamp_color(color));
}

// Fonction principale de lancer de rayon (trace)
t_vec3	trace(t_ray ray, t_scene scene)
{
	float	t_min;
	t_vec3	hit_normal;
	t_vec3	obj_color;
	t_vec3	hit_point;
	t_vec3	zero_vec;

	zero_vec.x = 0; zero_vec.y = 0; zero_vec.z = 0;
	t_min = 1e9;
	hit_normal = zero_vec;
	obj_color = zero_vec;
	scene.ray = ray;
	if (intersect_objects(&t_min, &hit_normal, &obj_color, scene))
	{
		hit_point = vec3_add(scene.ray.origin, vec3_scale(scene.ray.dir,
					t_min));
		return (calc_lighting(hit_point, hit_normal, obj_color, scene));
	}
	return (zero_vec);
}
