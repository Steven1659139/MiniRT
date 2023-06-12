/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:29:02 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/12 15:38:59 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	update_trigger_unselect(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_C))
	{
		vars->camera_trigger = !vars->camera_trigger;
		vars->selected = NULL;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_L))
	{
		vars->light_trigger = !vars->light_trigger;
		vars->selected = NULL;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		vars->selected = NULL;
		vars->ambient_trigger = !vars->ambient_trigger;
	}
}

void	print_info_scene(void)
{
	t_vars	*vars;

	vars = init_vars();
	if (vars->selected)
	{
		printf("OBJECT x = %f y = %f z = %f\n", \
		to_double(vars->selected->coord.x), \
		to_double(vars->selected->coord.y), \
		to_double(vars->selected->coord.z));
		printf("OBJECT_ORIENTATION x = %f y = %f z = %f\n", \
		to_double(vars->selected->orientation.x), \
		to_double(vars->selected->orientation.y), \
		to_double(vars->selected->orientation.z));
	}
	printf("CAMERA x = %f y = %f z = %f\n", \
	to_double(vars->camera->coord.x), \
	to_double(vars->camera->coord.y), to_double(vars->camera->coord.z));
	printf("LIGHT x = %f y = %f z = %f\n", \
	to_double(vars->light->coord.x), \
	to_double(vars->light->coord.y), to_double(vars->light->coord.z));
}

void	update_trigger(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_O))
		vars->orientation_trigger = !vars->orientation_trigger;
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_X))
		vars->x_trigger = !vars->x_trigger;
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_Y))
		vars->y_trigger = !vars->y_trigger;
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_Z))
		vars->z_trigger = !vars->z_trigger;
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_R))
		vars->radius_trigger = !vars->radius_trigger;
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_H))
		vars->height_trigger = !vars->height_trigger;
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_F))
		vars->fov_trigger = !vars->fov_trigger;
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_I))
		vars->interface_trigger = !vars->interface_trigger;
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_P))
		print_info_scene();
	update_trigger_unselect(vars);
}

void	update_ambient_light(t_vars *vars)
{
	if (vars->ambient_trigger)
	{
		if ((mlx_is_key_down(vars->mlx, 61) || \
		mlx_is_key_down(vars->mlx, 334)) && \
		(to_double(vars->ambient_light->light_ratio) + 0.1) < 1)
			set_value(&vars->ambient_light->light_ratio, \
			to_double(vars->ambient_light->light_ratio) + 0.1);
		if ((mlx_is_key_down(vars->mlx, 45) || \
		mlx_is_key_down(vars->mlx, 333)) && \
		(to_double(vars->ambient_light->light_ratio) - 0.1) > -0.01)
			set_value(&vars->ambient_light->light_ratio, \
			to_double(vars->ambient_light->light_ratio) - 0.1);
		printf("Ambient light ratio: %f\n", \
		round(to_double(vars->ambient_light->light_ratio) * 10) / 10);
		printf("Ambient Color = %X\n", vars->ambient_light->color);
	}
}

void	update_intensity(t_vars *vars)
{
	if (vars->light_trigger && vars->radius_trigger)
	{
		if ((mlx_is_key_down(vars->mlx, 61) || \
		mlx_is_key_down(vars->mlx, 334)) && \
		(to_double(vars->light->light_ratio) + 0.1) < 1)
			set_value(&vars->light->light_ratio, \
			to_double(vars->light->light_ratio) + 0.1);
		if ((mlx_is_key_down(vars->mlx, 45) || \
		mlx_is_key_down(vars->mlx, 333)) && \
		(to_double(vars->light->light_ratio) - 0.1) > -0.1)
			set_value(&vars->light->light_ratio, \
			to_double(vars->light->light_ratio) - 0.1);
		printf("Light intensity: %f\n", \
			round(to_double(vars->light->light_ratio) * 10) / 10);
	}
}

void	reset_position(t_vector3d *point)
{
	if (point->x < 0)
	{
		point->x = -point->x;
		point->y = -point->y;
		point->z = -point->z;
	}
}
