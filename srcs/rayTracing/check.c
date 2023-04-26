#include "../../include/miniRT.h"

double	check_sp(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double dist)
{
	t_Vector3d ro_sc = Vector3d_sub(ray.o, Point3d_to_Vector3d(s->coord));
	t_Vector3d abc;
	t_Vector2d t;

	abc.x =  Vector3d_dot(ray.d, ray.d);
	abc.y = 2.0 * Vector3d_dot(ray.d, ro_sc);
	abc.z = Vector3d_dot(ro_sc, ro_sc) - pow(to_double(s->radius), 2.0);

	double disc;
	double distance;
	if (!solveQuadratic(abc, &t, &disc))
		return (dist);
	distance = t.x;
	if (dist > distance) //distance comparaison
	{
		rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, distance));
		rh->color = s->color;
		rh->shape = (t_shape*)s;
		rh->distance = distance;
		return (distance);
	}
	return (dist);
}

double	check_pl(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double dist)
{
	t_Vector3d sc = Point3d_to_Vector3d(s->coord);
	t_Vector3d so = Point3d_to_Vector3d(s->orientation);

	double denom = Vector3d_dot(so, ray.d);
	if (fabs(denom) > 0)
	{
		double t = Vector3d_dot(Vector3d_sub(sc, ray.o), so) / denom;	
		if(dist >= t) //distance comparaison
		{
			if (t > 0) //only if t is positive
			{
				rh->color = s->color;
				rh->shape = (t_shape*)s;
				rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, t));
				rh->distance = t;
				return t;
			}
			else
				return (dist);
		}
	}
	return (dist);
}

double	check_cy(const t_shape *s,const  t_Ray ray, t_Ray_hit *rh, double dist)
{
	// Calculer l'équation du rayon
	t_Vector3d abc;
	t_Vector2d t;

	// Calculer les coefficients de l'équation quadratique
	abc.x = (ray.d.x * ray.d.x) + (ray.d.y * ray.d.y);
	abc.y = 2.0 * (ray.o.x * ray.d.x + ray.o.y * ray.d.y);
	abc.z = ray.o.x * ray.o.x + ray.o.y * ray.o.y - to_double(s->radius) * to_double(s->radius);
	// calculer le discriminant
	double discriminant;

	// Vérifier si le rayon intersecte le cylindre
	if (!solveQuadratic(abc, &t, &discriminant))
		return dist;

	// Choisir la plus petite distance positive
	double distance = 0;
	if (t.x > 0.0 && (t.y < 0.0 || t.x < t.y)) 
	{
		// Vérifier si l'intersection est dans la hauteur du cylindre
		double z1 = ray.o.z + t.x * ray.d.z;
		
		if (z1 >= to_double(s->coord.z) - to_double(s->height) / 2.0 && z1 <= to_double(s->coord.z) + to_double(s->height )/ 2.0) 
			distance = t.x;
	}
	if (distance < 0.0) 
	{
		if (t.y > 0.0 && (t.x < 0.0 || t.y < t.x)) 
		{
			// Vérifier si l'intersection est dans la hauteur du cylindre
			double z2 = ray.o.z + t.y * ray.d.z;
			
			if (z2 >= to_double(s->coord.z) - to_double(s->height) / 2.0 && z2 <= to_double(s->coord.z) + to_double(s->height )/ 2.0)
				distance = t.y;
		}
	}
	// Vérifier si une intersection a été trouvée
	if (distance)
		return dist;
	// Remplir la structure t_Ray_hit avec les informations de l'intersection
	if(dist > distance)
	{
		rh->distance = distance;
		rh->color = s->color;
		rh->shape = (t_shape*)s;
		rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, distance));
		return distance;
	}
	return dist;
}

/// @brief Checks if the dot product of both vectors created from the sphere is the same sign
/// @param shape_pos position vector of the shape.
/// @param Vec1 position vector of the vec1.
/// @param Vec2 position vector of the vec2.
/// @return 
bool	check_dot_sign(t_Vector3d shape_pos, t_Vector3d Vec1, t_Vector3d Vec2)
{
	double dot1 = Vector3d_dot(shape_pos, Vec1);
	double dot2 = Vector3d_dot(shape_pos, Vec2);

	if (dot1 >= 0 && dot2 >= 0)
		return (true);
	else if (dot1 >= 0 && dot2 >= 0)
		return (true);
	else
		return (false);
}


/// @brief 			:Check for the intersection of each object with the provided t_Ray
/// @param ray		:The ray
/// @param rh		:The t_Ray_hit containing intersection information
/// @param distance :The distance to compare if dist == old_dist nothing is intersected
/// @param shape_o	:The object(self) it needs to ignore
/// @return			:Returns a bool if the ray hit(True) or not(false) an object
bool	ray_checkhit(const t_Ray ray, t_Ray_hit *rh, double *distance, t_shape *shape_o)
{
	t_node *aff = init_vars()->objs->first;
	double old_dist = *distance; //Should dist be distance?

	while(aff)
	{
		t_shape *s = aff->content;

		if (!shape_o || s->index != shape_o->index) //if the object is not itself
		{
			if (ft_strcmp(s->id, "cy"))
				*distance = check_cy(s, ray, rh, *distance);
			else if (ft_strcmp(s->id, "pl"))
				*distance = check_pl(s, ray, rh, *distance);
			else if (ft_strcmp(s->id, "sp"))
				*distance = check_sp(s, ray, rh, *distance);
		}
		aff = aff->next;
	}
	if (*distance >= old_dist && !rh->bounced) 
		return (false); //if the distance is the same or farther, it has touched nothing.
	else if (!rh->bounced)
		return (true); //if shorter, it has touched.
	else if(*distance == old_dist && rh->bounced)
		return (true); //if ray is bounced (should see if something interrupting light), if distance is same it has touched
	else
		return (false);
}
