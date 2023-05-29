/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayTracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:54:19 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/26 17:21:05 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	ray_to_screen(void)
{
	uint32_t	x;
	uint32_t	y;
	t_Ray		ray;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray = ray_init_to_screen(init_vars(), x, y);
			mlx_put_pixel((init_vars()->img), x, y, ray_tracing(ray));
		}
	}
}

t_Ray_hit	init_ray_hit(void)
{
	t_Ray_hit	rh;

	rh.color = 0;
	rh.coord = vector3d_init(0, 0, 0);
	rh.distance = 0;
	rh.normal = vector3d_init(0, 0, 0);
	rh.shape = NULL;
	rh.hit = false;
	return (rh);
}

t_Ray_hit	ray_trace(const t_Ray ray, double dist_bef, t_shape *shape)
{
	t_Ray_hit	light_ray_hit;
	double		distance;

	distance = dist_bef;
	light_ray_hit = init_ray_hit();
	light_ray_hit.bounced = false;
	if (!shape)
		ray_checkhit(ray, &light_ray_hit, &distance, NULL);
	else
	{
		light_ray_hit.bounced = true;
		ray_checkhit(ray, &light_ray_hit, &distance, shape);
	}
	return (light_ray_hit);
}

uint32_t	ray_tracing(const t_Ray ray)
{
	uint32_t	color;
	t_Ray_hit	hit;

	hit = ray_trace(ray, INFINITY, NULL);
	if (!hit.color)
		return (BLACK);
	color = 0;
	color = rgba_to_int32_t(shading(&hit));
	return (color);
}
