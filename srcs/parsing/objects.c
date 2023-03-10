#include "../../include/miniRT.h"

t_shape   *object_A(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
    S->id = elem[0];
    S->light_ratio = str_to_fixed(elem[1]);
	S->color = RGB_to_hex(elem[2]);
    return(S);
}

t_shape *object_C(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	// S->coord = elem[1];
	// S->orientation = elem[2];
	S->FOV = ft_atoi(elem[3]);
	return (S);
}

t_shape *object_L(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	// S->coord = elem[1];
	S->light_ratio = str_to_fixed(elem[2]);
	if (elem[3])
		S->color = RGB_to_hex(elem[3]);
	return (S);
}

t_shape *object_sp(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	// S->coord = elem[1];
	S->diameter = str_to_fixed(elem[2]);
	S->color = RGB_to_hex(elem[3]);
	return (S);
}

t_shape *object_pl(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	// S->coord = elem[1];
	// S->orientation = elem[2];
	S->color = RGB_to_hex(elem[3]);
	return (S);
}

t_shape *object_cy(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	// S->coord = elem[1];
	// S->orientation = elem[2];
	S->diameter = str_to_fixed(elem[3]);
	S->height = str_to_fixed(elem[4]);
	S->color = RGB_to_hex(elem[5]);
	return (S);
}

void	print_objects(t_dlist *l)
{
	t_node *aff = l->first;

	while(aff)
	{
		t_shape *s = aff->content;

		if (ft_strcmp(s->id, "A")){
			printf("ID:\t%s\n", s->id);
			printf("LRatio:\t%d,%d\n", s->light_ratio.entier, s->light_ratio.decimal);
			printf("Color:\t%X\n", s->color);
		}
		else if (ft_strcmp(s->id, "C")){
			printf("ID:\t%s\n", s->id);
            printf("FOV:\t%d\n", s->FOV);
		}
		else if (ft_strcmp(s->id, "L")){
			printf("ID:\t%s\n", s->id);
			printf("LRatio:\t%d,%d\n", s->light_ratio.entier, s->light_ratio.decimal);
			printf("Color:\t%X\n", s->color);
		}
		else if (ft_strcmp(s->id, "sp")){
			printf("ID:\t%s\n", s->id);
			printf("Dia.:\t%d,%d\n", s->diameter.entier, s->diameter.decimal);
			printf("Color:\t%X\n", s->color);
		}
		else if (ft_strcmp(s->id, "pl")){
			printf("ID:\t%s\n", s->id);
			printf("Color:\t%X\n", s->color);
		}
		else if (ft_strcmp(s->id, "cy")){
			printf("ID:\t%s\n", s->id);
			printf("Dia.:\t%d,%d\n", s->diameter.entier, s->diameter.decimal);
			printf("Height:\t%d,%d\n", s->height.entier, s->height.decimal);
			printf("Color:\t%X\n", s->color);
		}
		printf("------------------------------\n");
		aff = aff->next;
	}

}