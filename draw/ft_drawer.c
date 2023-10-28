/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:03:30 by ohachami          #+#    #+#             */
/*   Updated: 2023/09/14 19:03:34 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point	assign_point(double x, double y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_point	assign_int_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

int	check_inside(t_window *win, t_point *player)
{
	int	i;
	int	j;

	i = (player->y - 2) / 10;
	j = (player->x - 2) / 10;
	//ft_printf("x=%d,y=%d,angle=[%d][%d]\n",win->map.lenght,win->map.wide,  i, j);
	if (win->map.mapo[i][j] != '0' && win->map.mapo[i][j] != 'W') //will cause probleme
		return (0);
	return (1);
}

t_point	mov_player(t_player player, t_vector v, mlx_t *mlxp)
{
	double	speed;
	t_point	dir;

	speed = 0.25;
	dir = player.p;
	if (mlx_is_key_down(mlxp, MLX_KEY_W))
		dir = assign_point(player.p.x + speed * v.x,
				player.p.y + speed * v.y);
	if (mlx_is_key_down(mlxp, MLX_KEY_S))
		dir = assign_point(player.p.x - speed * v.x,
				player.p.y - speed * v.y);
	if (mlx_is_key_down(mlxp, MLX_KEY_D))
		dir = assign_point(player.p.x + speed * v.y,
				player.p.y - speed * v.x);
	if (mlx_is_key_down(mlxp, MLX_KEY_A))
		dir = assign_point(player.p.x - speed * v.y,
				player.p.y + speed * v.x);
	printf("x=%.2f,y=%.2f, v.x=%f, v.y=%f angle=%.2f\n", dir.x, dir.y,
		speed * v.x, speed * v.y, player.angle);
	return (dir);
}

void	keyhook(void *param)
{
	t_window	*win;
	t_point		start;
	t_vector	v;

	win = (t_window *)param;
	mlx_delete_image(win->mlx_ptr, win->img);
	mlx_delete_image(win->mlx_ptr, win->mini_map);
	start = win->player.p;
	win->mini_map = mlx_new_image(win->mlx_ptr, win->map.lenght * 50 + 20,
			win->map.wide * 50 + 20);
	win->img = mlx_new_image(win->mlx_ptr, win->map.lenght * 10 + 4,
			win->map.wide * 10 + 4);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_RIGHT))
		win->player.angle = angle_adjast(win->player.angle, '+');
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_LEFT))
		win->player.angle = angle_adjast(win->player.angle, '-');
	v.x = 1;
	v.y = 0;
	v = rotation_vect(v, angle_adjast(win->player.angle, '*'));
	start = mov_player(win->player, v, win->mlx_ptr);

	v = ft_draw_map(win, win->map.mapo, &start, v);
	//ft_draw_scene(win, &win->player.p, lv);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	mlx_image_to_window(win->mlx_ptr, win->mini_map, 0, 0);
}

void	init_val(t_window	*win)
{
	t_vector	v;

	win->mlx_ptr = mlx_init(win->map.lenght * 50 + 20,
			win->map.wide * 50 + 20, "Super Duper Cool 3D Game!!!", true);
	if (!win->mlx_ptr)
		error();
	win->img = mlx_new_image(win->mlx_ptr,
			win->map.lenght * 10 + 4, win->map.wide * 10 + 4);
	if (!win->img)
		error();
	win->mini_map = mlx_new_image(win->mlx_ptr,
			win->map.lenght * 50 + 20, win->map.wide * 50 + 20);
	if (!win->img)
		error();
	v.x = 1;
	v.y = 0;
	v = rotation_vect(v, angle_adjast(win->player.angle, '*'));
	//win->player.p = assign_point(60 + 5, 22 + 5);
	win->player.angle = 0;
	printf("|x=%d,y=%d\n", win->map.lenght * 50 + 20, win->map.wide * 50 + 20);
	ft_draw_map(win, win->map.mapo, &win->player.p, v);
	mlx_loop_hook(win->mlx_ptr, &keyhook, win);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	mlx_image_to_window(win->mlx_ptr, win->mini_map, 0, 0);
	mlx_loop(win->mlx_ptr);
}
