#include "../../include/miniRT.h"

double	check_sp(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double dist)
{

	t_Vector3d ro_sc = Vector3d_sub(ray.o, Point3d_to_Vector3d(s->coord));
	t_Vector3d abc;
	t_Vector2d t;

	abc.x =  Vector3d_dot(ray.d, ray.d);
	abc.y = 2.0 * Vector3d_dot(ray.d, ro_sc);
	abc.z = Vector3d_dot(ro_sc, ro_sc) - pow(to_double(s->radius), 2);

	double disc;
	double distance;
	if (!solveQuadratic(abc, &t, &disc))
		return (dist);
	double q;
	if (abc.y < 0)
		q = (-abc.y - sqrt(disc)) / 2.0;
	else
		q = (-abc.y + sqrt(disc)) / 2.0;
	t.x = q / abc.x;
	t.y = abc.z / q;
	if (t.y < 0)
		return (dist);
	else if(t.x < 0)
		distance = t.y; //t0
	else
		distance = t.x; //t1
	if (dist >= distance) //distance comparaison
	{
		rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, distance));
		rh->color = s->color;
		rh->shape = (t_shape*)s;
		return (distance);
	}
	return (dist);
}

double	check_pl(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double dist)
{
	t_Vector3d sc = Point3d_to_Vector3d(s->coord);
	t_Vector3d so = Point3d_to_Vector3d(s->orientation);

	double denom = Vector3d_dot(so, ray.d);
	if (fabs(denom) > 1e-6){
		double t = Vector3d_dot(Vector3d_sub(sc, ray.o), so) / denom;	
		if(dist > t) //distance comparaison
		{
			if (t > 0) //only if t is positive
			{
				rh->color = s->color;
				rh->shape = (t_shape*)s;
				rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, t));
				return t;
			}
			else
				return (dist);
		}
		return (dist);
	}
	return (dist);
}

double	check_cy(const t_shape *s,const  t_Ray ray, t_Ray_hit *rh, double dist)
{
	// Calculer l'équation du rayon
	t_Vector3d o = ray.o;//optional just write ray.o for each
	t_Vector3d d = ray.d;//optional just write ray.d for each
	t_Vector3d abc;
	t_Vector2d t;

	// Calculer les coefficients de l'équation quadratique
	abc.x = (d.x * d.x) + (d.y * d.y);
	abc.y = 2.0 * (o.x * d.x + o.y * d.y);
	abc.z = o.x * o.x + o.y * o.y - s->radius.value * s->radius.value;
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
		double z1 = o.z + t.x * d.z;
		
		if (z1 >= to_double(s->coord.z) - to_double(s->height) / 2.0 && z1 <= to_double(s->coord.z) + to_double(s->height )/ 2.0) 
			distance = t.x;
	}
	if (distance < 0.0) 
	{
		if (t.y > 0.0 && (t.x < 0.0 || t.y < t.x)) 
		{
			// Vérifier si l'intersection est dans la hauteur du cylindre
			double z2 = o.z + t.y * d.z;
			
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
		rh->coord = Vector3d_add(o, Vector3d_mult(d, distance));
		return distance;
	}
	return dist;

}


void	ray_checkhit(const t_Ray ray, t_Ray_hit *rh, double *distance){
	t_Vars *vars = init_vars();
	t_node *aff = vars->objs->first;
	rh->color = 0;
	rh->shape = NULL;
	while(aff)
	{
		t_shape *s = aff->content;
		if (ft_strcmp(s->id, "sp"))
			*distance = check_sp(s, ray, rh, *distance);
		else if (ft_strcmp(s->id, "cy"))
			*distance = check_cy(s, ray, rh, *distance);
		else if (ft_strcmp(s->id, "pl"))
			*distance = check_pl(s, ray, rh, *distance);
		aff = aff->next;
	}
	return ;
}
