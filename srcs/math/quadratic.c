/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:33:32 by ast-jean          #+#    #+#             */
/*   Updated: 2023/05/29 10:34:36 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_Vector3d	assign_var_quad(t_Vector3d d, t_Vector3d e, const t_shape *c)
{
	t_Vector3d	abc;

	abc.x = vector3d_dot(d, d);
	abc.y = 2.0 * vector3d_dot(d, e);
	abc.z = vector3d_dot(e, e) - to_double(c->radius) * to_double(c->radius);
	return (abc);
}

void	swap_quad(t_Vector2d *t)
{
	double	tmp;

	if (t->x > t->y)
	{
		tmp = t->y;
		t->y = t->x;
		t->x = tmp;
	}
}

bool	solve_quadratic(t_Vector3d abc, t_Vector2d *t)
{
	double	q;
	double	discr;

	discr = pow(abc.y, 2) - 4 * abc.x * abc.z;
	if (discr < 0)
		return (false);
	else if (discr == 0)
	{
		t->x = -0.5 * abc.y / abc.x;
		t->y = -0.5 * abc.y / abc.x;
	}
	else
	{
		if (abc.y > 0)
			q = -0.5 * (abc.y + sqrt(discr));
		else
			q = -0.5 * (abc.y - sqrt(discr));
		if (q < 0)
			return (false);
		t->x = q / abc.x;
		t->y = abc.z / q;
	}
	swap_quad(t);
	return (true);
}
