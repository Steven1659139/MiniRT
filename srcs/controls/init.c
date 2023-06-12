/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:37:03 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/12 11:59:15 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_trigger(t_vars *vars)
{
	vars->x_trigger = 0;
	vars->y_trigger = 0;
	vars->z_trigger = 0;
	vars->radius_trigger = 0;
	vars->camera_trigger = 0;
	vars->orientation_trigger = 0;
	vars->interface_trigger = 0;
	vars->height_trigger = 0;
	vars->fov_trigger = 0;
	vars->light_trigger = 0;
	vars->ambient_light = 0;
}

t_vars	*init_vars(void)
{
	static t_vars	*vars;

	if (!vars)
	{
		vars = malloc(sizeof(t_vars));
		vars->camera = NULL;
		vars->light = NULL;
		vars->ambient_light = NULL;
		vars->objs = malloc(sizeof(t_dlist));
		vars->objs->first = NULL;
		vars->objs->last = NULL;
		vars->error_message = NULL;
		vars->selected = NULL;
		vars->distance_to_screen = 0;
		vars->i = 0;
		vars->nbr_obj = 0;
		init_trigger(vars);
	}
	return (vars);
}

void	reinit_triggers(t_vars *vars, t_ray_hit hit)
{
	vars->ambient_trigger = false;
	vars->camera_trigger = false;
	vars->light_trigger = false;
	vars->selected = hit.shape;
}
