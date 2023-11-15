/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:33:00 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/13 10:33:04 by ohachami         ###   ########.fr       */
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

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	int				floor;
	int				ceileng;
}t_texture;

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
	int	x;
	int	y;
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
	t_point		p; // put player position 
	double		angle; // put angle here
	t_vector	v;
	double		speed; // this is a fixed value
}t_player;

typedef struct s_ray
{
	t_point	p;
	double	dist;
	char	side;
}t_ray;

typedef struct s_map
{
	int		lenght; // the x len of the map
	int		wide; // the y len of the map
	char	**elem; // all the file is here
	char	**mapo; // put the map here
}t_map;

typedef struct s_window
{
	void		*win_ptr;
	t_player	*player; // put player position and angle here
	mlx_image_t	*mini_map;
	mlx_image_t	*img;
	mlx_t		*mlx_ptr;
	t_map		map;
	t_texture	t; // put texture and floor && celein colore here
	t_cord		*screen; // those are fix
}t_window;

void		ft_start_map(char *map);
void		draw_line(t_window *win, t_point start, t_point end);
void		cub_drawer(mlx_image_t *img, t_point start, t_point end, int color);
void		player_drawer(t_window *win, t_point pos, int color);
t_vector	ft_draw_map(t_window *win, char **matrix, t_point next_pos,
				t_vector v);
t_point		assign_point(double x, double y);
t_point		assign_int_point(int x, int y);
double		angle_adjast(double angle, char sign);
void		init_val(t_window *win);
t_vector	assign_vect(double vx, double vy, double angle);
t_point		pos_adjast(t_window *win, t_point pos);

int			check_inside(t_window *win, t_point player);
t_segm	wall(t_cord cord, t_window *win, t_vector v, int is_it_x);
t_ray		draw_scene(t_window *win, t_point next_pos, t_ray r);
t_vector	rotation_vect(t_vector vect, double deg);
void		draw_background(t_window *win, int floor, int ceiling);
void		draw_line(t_window *win, t_point start, t_point end);
void		cub_drawer(mlx_image_t *img, t_point start, t_point end, int color);

void		texturess(t_window *win, t_ray r, t_cord cord);
t_ray		raycast(t_window *win, int side, t_point pos, t_vector v);
//t_ray		raycast(t_window *win, int side, t_vector v, t_cord cord);
int			ft_color(int r, int g, int b);
double		norme_vect(t_vector vect);
double		dot_vect(t_vector vect, t_vector vect2);
t_cord		assign_cord(int x, int y);
t_point		in_cube_pos(t_window *win, t_cord cord, t_vector v);

int			check_first_line(char *str);
void		check_zero_surrond(char **strs);
void		check_tab(char **strs);
void		check_map(char **strs);
void		error(void);
void		free_all(t_window *win, char **elem);
void		ft_start(int i, char **strs);

#endif
