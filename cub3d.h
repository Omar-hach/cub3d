/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:16:50 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/28 11:54:14 by sbellafr         ###   ########.fr       */
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
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}t_textures;

typedef struct s_color
{
	int	t;
	int	r;
	int	b;
	int	g;
}t_color;

typedef struct s_vector
{
	double	x;
	double	y;
}t_vector;

typedef struct s_point
{
	double	x;
	double	y;
}t_point;

typedef struct s_cord
{
	int	i;
	int	j;
}t_cord;

typedef struct s_contact
{
	t_point	r;
	double	distance;
}t_contact;

typedef struct s_segm
{
	t_point	start;
	t_point	end;
}t_segm;

typedef struct s_player
{
	t_point		p;
	double		angle;
	t_vector	v;
}t_player;

typedef struct s_ray
{
	t_point		p;
	double		distance;
	char		side;
}t_ray;

typedef struct s_map
{
	int		lenght;
	int		wide;
	char	**elem;
	char	**mapo;
}t_map;

typedef struct s_window
{
	void		*win_ptr;
	int			walls_num;
	t_player	*player;
	mlx_image_t	*mini_map;
	mlx_image_t	*img;
	mlx_t		*mlx_ptr;
	t_map		map;
	t_color		*floor;
	t_color		*ceiling;
	mlx_texture_t		*texture;
}t_window;

void		ft_start_map(char *map);
void		draw_line(t_window *win, t_point start, t_point end);
void		cub_drawer(mlx_image_t *img, t_point start, t_point end, int color);
void		player_drawer(t_window *win, t_point pos, int color);
t_vector	ft_draw_map(t_window *win, char **matrix, t_point next_pos, t_vector v);
t_point		assign_point(double x, double y);
t_point		assign_int_point(int x, int y);
double		angle_adjast(double angle, char sign);
void		init_val(t_window *win);
t_vector	assign_vect(double x, double y, t_point pos);
t_point		pos_adjast(t_window *win, t_point pos);

int			check_inside(t_window *win, t_point player);
t_segm		wall(t_cord cord, t_window *win, t_point step, int is_it_x);
void		ft_draw_scene(t_window *win, t_point *pos, t_vector lv);
t_vector	rotation_vect(t_vector vect, double deg);

int		check_first_line(char *str);
void	check_zero_surrond(char **strs);
int		check_textures(char **strs, t_textures *t, t_color *floor, t_color *ceiling);
void	check_tab(char **strs);
void	check_map(char **strs);
void	error(void);

#endif
