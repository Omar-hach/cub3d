/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:06:30 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/14 16:06:33 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


void	draw_line(t_window *win, t_point start, t_point end)
{
	t_point	dp;
	t_point	pk;
	double	step;
	int		i;

	dp.x = end.x - start.x;
	dp.y = end.y - start.y;
	pk.x = start.x;
	pk.y = start.y;
	if (fabs(dp.x) > fabs(dp.y))
		step = fabs(dp.x);
	else
		step = fabs(dp.y);
	i = -1;
	while (++i < step)
	{
		if(pk.x > win->screen->x && pk.y > win->screen->y
				&& pk.x < 0 && pk.y < 0)
					return ;
		mlx_put_pixel(win->img, pk.x, pk.y, 0xFF322BFF);
		pk.x += dp.x / step;
		pk.y += dp.y / step;
	}
}

void	player_drawer(t_window *win, t_point pos, int color)
{
	int		r;
	double	deg;

	r = -1;
	deg = 0;
	while (++r < 2)
	{
		deg = 0;
		while (deg < M_PI * 2)
		{
			if(pos.y < 0 && pos.x < 0 && pos.x > win->screen->x && pos.y > win->screen->y)
				return ;
			mlx_put_pixel(win->img, pos.x + r * cos(deg),
					pos.y + r * sin(deg), color);
			deg += M_PI / 180;
		}
	}
}

void	draw_mini_map(t_window *win, char **matrix)
{
	int		x;
	int		y;
	t_point	start;
	t_point	end;

	x = -1;
	y = -1;
	start = assign_int_point(0, 0);
	end = assign_int_point(win->map->wide * 10 + 4, win->map->len * 10 + 4);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_int_point(10, 10);
	while (++x < win->map->wide)
	{
		y = -1;
		while (++y < win->map->len && matrix[x][y])
		{
			start = assign_int_point(y * 10 + 2, x * 10 + 2);
			if (matrix[x][y] == '1')
				cub_drawer(win->img, start, end, 0x09005EFF);
			else if (matrix[x][y] != '1'
			&& matrix[x][y] != ' ' && matrix[x][y] != '\n')
				cub_drawer(win->img, start, end, 0xB8A649FF);
		}
	}
	player_drawer(win, win->player->p, 0xFF322BFF);
}

int	check_inside_b(t_window *win, t_point player)
{
	int	i;
	int	j;

	i = (player.y + 1) / 10;
	j = (player.x + 1) / 10;
	if (win->map->mapo[i][j] == '1' || win->map->mapo[i][j] == ' '
			|| !win->map->mapo[i][j])
		return (0);
	i = (player.y - 5) / 10;
	j = (player.x - 5) / 10;
	if (win->map->mapo[i][j] == '1' || win->map->mapo[i][j] == ' '
			|| !win->map->mapo[i][j])
		return (0);
	i = (player.y - 2) / 10;
	j = (player.x - 2) / 10;
	if (win->map->mapo[i][j] == '1' || win->map->mapo[i][j] == ' '
			|| !win->map->mapo[i][j])
		return (0);
	return (1);
}

t_ray	draw_scene_b(t_window *win, t_point next_pos)
{
	double		plane;
	t_cord		cord;
	t_cord		pixel;
	t_ray		r;
	t_vector	plane_v;

	pixel = assign_cord(-1, 0);
	cord = assign_cord((win->player->p.x - 2) / 10,
			(win->player->p.y - 2) / 10);
	if (check_inside_b(win, next_pos))
		win->player->p = assign_point(next_pos.x, next_pos.y);
	while (++pixel.x < win->screen->x)
	{
		plane = (2 * (double)pixel.x / 40 - 32) * M_PI / (double)180;
		plane_v = assign_vect(win->player->speed, 0,
				win->player->angle + plane);
		r = raycast(win, 1, plane_v, cord);
		pixel.y = (win->screen->y - win->screen->y / r.dist * 10) / 2 - 1;
		texturess(win, r, pixel);
	}
	r = raycast(win, 0, win->player->v, cord);
	return (r);
}

void	keyhook_b(void *param)
{
	t_window	*win;
	t_point		next_pos;
	t_ray		r;

	win = (t_window *)param;
	mlx_delete_image(win->mlx_ptr, win->img);
	win->img = mlx_new_image(win->mlx_ptr,
			win->screen->x, win->screen->y);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_RIGHT))// || mlx_is_mouse_down(win->mlx_ptr, MLX_MOUSE_BUTTON_RIGHT))
		win->player->angle = angle_adjast(win->player->angle, '+');
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_LEFT))// || mlx_is_mouse_down(win->mlx_ptr, MLX_MOUSE_BUTTON_LEFT))
		win->player->angle = angle_adjast(win->player->angle, '-');
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(win->mlx_ptr, win->img);
		free_all(win, win->map->mapo);
		exit(0);
	}
	draw_background(win, ft_color(120, 0, 00), ft_color(0, 0, 120));
	win->player->v = assign_vect(win->player->speed, 0, win->player->angle);
	next_pos = mov_player(win->player->p, win->player->v, win->mlx_ptr);
	r = draw_scene_b(win, next_pos);
	draw_mini_map(win, win->map->mapo);
	draw_line(win, win->player->p, r.p);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
}
