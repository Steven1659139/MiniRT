
#ifndef VECTORS_H
# define VECTORS_H

#include "miniRT.h"

typedef struct s_Vars t_Vars;

typedef struct s_Vector2d{
    double x;
	double y;
} t_Vector2d;

typedef struct s_Vector3d{
    double x;
	double y;
	double z;
} t_Vector3d;

typedef struct s_Ray{
    t_Vector3d o;
	t_Vector3d d;
} t_Ray;

typedef struct s_Ray_hit{
    double		distance;
	uint32_t	color;
	t_shape		*shape;
	t_Vector3d	coord;
	t_Vector3d	normal;
	bool		hit;
	bool		bounced;
} t_Ray_hit;

/*-------------------------Vectors_ops.c--------------------------*/
t_Vector3d	vector3d_add(t_Vector3d a, t_Vector3d b);
t_Vector3d	vector3d_sub(t_Vector3d a, t_Vector3d b);
t_Vector3d	vector3d_mult(t_Vector3d v, double b);
t_Vector3d	vector3d_mult3d(t_Vector3d v, t_Vector3d b);
t_Vector3d	vector3d_unit(t_Vector3d v);
/*-------------------------Vectors.c--------------------------*/
t_Vector3d	vector3d_init(double x, double y, double z);
double		vector3d_dot(t_Vector3d a, t_Vector3d b);
t_Vector3d	vector3d_cross(t_Vector3d a, t_Vector3d b);
double		vector3d_length(t_Vector3d v);
t_Vector3d 	vector3d_norm(const t_Vector3d v);
/*-------------------------Ray.c--------------------------*/
t_Ray ray_init(t_Vector3d origin, t_Vector3d direction);
t_Ray ray_init_to_screen(t_Vars *v, int x, int y);
t_Vector3d ray_direction(t_Vector3d from, t_Vector3d to);

#endif