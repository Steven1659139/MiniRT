/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:25:43 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/29 10:20:31 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_Vector3d	point3d_to_vector3d(t_3dPoint point)
{
	t_Vector3d	vec;

	vec.x = to_double(point.x);
	vec.y = to_double(point.y);
	vec.z = to_double(point.z);
	return (vec);
}

t_3dPoint	vec3d_to_point3d(t_Vector3d vec)
{
	t_3dPoint	point;

	point.x = fp_init(vec.x);
	point.y = fp_init(vec.y);
	point.z = fp_init(vec.z);
	return (point);
}

t_Fixed	fp_init(double value)
{
	t_Fixed	fp;

	set_value(&fp, value);
	return (fp);
}

void	set_value(t_Fixed *fp, double value)
{
	fp->value = value * fp_scale;
}

double	to_double(t_Fixed fp)
{
	return ((double) fp.value / fp_scale);
}
