
#pragma once
#ifndef _MINI_RT_H_
# define _MINI_RT_H_

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft_dlist/dlist.h"
# include "objects.h"

#define BLACK	0x000000FF
#define WHITE	0xFFFFFFFF
#define GRAY	0x888888FF
#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF

#define fixed_scale 256



typedef struct s_Vars	// all of our values needed throught the program
{
	int32_t env3D[100000][100000][100000];
	mlx_image_t* img;
	mlx_t		*mlx;
	void		*objs;
} t_Vars;


//parsing
void	parse(int argc, char **argv, t_dlist *l);
void	error_exit(char *str);
void	valid_file(char *file);
void	split(char *file, t_dlist *l);
void	valid_element(char **elem, t_dlist *l);
//objects
t_shape   *object_A(char **elem);

//fixed.c
void	set_value(t_Fixed *fp, double value);
int	to_int(t_Fixed fp);
double	to_double(t_Fixed fp);
double	fp_cal(char operand, int num_args, ...);


#endif