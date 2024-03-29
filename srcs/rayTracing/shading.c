/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:53:59 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/14 09:24:33 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

double	find_angle_normals(t_vector3d Norm1, t_vector3d Norm2)
{
	double	mag1;
	double	mag2;
	double	dot;

	dot = vector3d_dot(Norm1, Norm2);
	mag1 = sqrt \
	((Norm1.x * Norm1.x) + (Norm1.y * Norm1.y) + (Norm1.z * Norm1.z));
	mag2 = sqrt \
	((Norm2.x * Norm2.x) + (Norm2.y * Norm2.y) + (Norm2.z * Norm2.z));
	return (dot / (fabs(mag1) * fabs(mag2)));
}

t_rgba	shading_obj(t_ray_hit hit_light, t_shape shape, \
t_ray_hit *first_hit, t_vector3d l_c)
{
	t_rgba		color;	
	t_vector3d	light_dir;
	t_vector3d	obj_normal;
	double		coeff;

	color = rgba_init(0, 0, 0);
	light_dir = light_normal(first_hit->coord, l_c);
	obj_normal = find_normal(first_hit->coord, \
	point3d_to_vector3d(shape.coord), shape, light_dir);
	coeff = fmax(0, find_angle_normals(light_dir, obj_normal));
	color = rgba_add(color, mix_colors_light(hit_light, shape, coeff));
	return (color);
}

t_rgba	shading(t_ray_hit *hit)
{
	t_vector3d	lc;
	t_ray		ray_s2l;
	double		distance;
	t_ray_hit	bounce;

	lc = point3d_to_vector3d(init_vars()->light->coord);
	ray_s2l = ray_init(hit->coord, \
	vector3d_norm(vector3d_sub(hit->coord, lc)));
	distance = find_distance(hit->coord, lc);
	ray_s2l.o = lc;
	bounce = ray_trace(ray_s2l, distance, hit->shape);
	return (shading_obj(bounce, *hit->shape, hit, lc));
}
