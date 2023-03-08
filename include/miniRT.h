/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:58:16 by ast-jean          #+#    #+#             */
/*   Updated: 2023/03/06 11:19:01 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef _MINI_RT_H_
# define _MINI_RT_H_

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft_dlist/dlist.h"

#define BLACK	0x000000FF
#define WHITE	0xFFFFFFFF
#define GRAY	0x888888FF
#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF

typedef struct s_Fixed{
	int	value;
	//slavoie
}	t_Fixed;

typedef struct s_2dPoint{
    t_Fixed x;
	t_Fixed y;
} t_2dPoint;

typedef struct s_3dPoint{
    t_Fixed x;
	t_Fixed y;
	t_Fixed z;
	int32_t		color;
} t_3dPoint;

typedef struct s_Vars	// all of our values needed throught the program
{
	t_3dPoint	*env3D;
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


#endif