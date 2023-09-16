/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:16:50 by sbellafr          #+#    #+#             */
/*   Updated: 2023/09/16 18:35:59 by sbellafr         ###   ########.fr       */
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
typedef struct s_textures
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *f;
	char *c;

}t_textures;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}t_point;

typedef struct s_player
{
	t_point p;
	int angle;
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
	mlx_image_t *img2;
	mlx_t		*mlx_ptr;
    t_map       map;
}t_window;



void	ft_start_map(char *map);
void	draw_line(t_window *win, t_point start, t_point end);
void	cub_drawer(mlx_image_t *img, t_point start, t_point end, int color);
t_point	player_drawer(mlx_image_t *img, t_point pos, t_player player,  int color);
void	ft_draw_map(t_window *win, char **matrix, t_player *player);
t_point	assign_point(int x, int y, int color);
int		angle_adjast(int angle, char sign);
void	init_val(t_window	*win);
int		check_first_line(char *str);
void	check_zero_surrond(char **strs);
void    check_textures(char **strs, t_textures *t);
void	error(void);

#endif


