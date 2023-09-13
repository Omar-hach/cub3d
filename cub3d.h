/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:16:50 by sbellafr          #+#    #+#             */
/*   Updated: 2023/09/13 20:43:18 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "libft/print/ft_printf.h"
# include "libft/get_next_line/get_next_line_bonus.h"
# include "MLX42/MLX42.h"
//# define PI 3.141592653589793
# define RAD 0.0174533

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}t_point;

typedef struct s_player
{
	t_point p;
	float angle;
}t_player;

typedef struct s_color
{
	int	t;
	int	r;
	int	b;
	int	g;
}t_color;

typedef struct s_map
{
	int		lenght;
	int		wide;
	int		width;
	char	**elem;
}t_map;

typedef struct s_window
{
	void		*win_ptr;
	t_player	player;
	mlx_image_t	*img;
	mlx_t		*mlx_ptr;
    t_map       map;
}t_window;



void    ft_start_map(char *map);

#endif


