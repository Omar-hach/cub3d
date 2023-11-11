/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:37:09 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/09 00:37:12 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		if (pk.x > 0 && pk.y > 0)
			mlx_put_pixel(win->img, pk.x, pk.y, 0xFF322BFF);
		pk.x += dp.x / step;
		pk.y += dp.y / step;
	}
}

void	cub_drawer(mlx_image_t *img, t_point start, t_point end, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < end.x - 1)
	{
		j = 0;
		while (j < end.y - 1)
		{
			mlx_put_pixel(img, start.x + j, start.y + i, color);
			j++;
		}
		i++;
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
			mlx_put_pixel(win->img, pos.x + r * cos(deg),
				pos.y + r * sin(deg), color);
			deg += M_PI / 180;
		}
	}
}

void	draw_background(t_window *win, int floor, int ceiling)
{
	t_point	start;
	t_point	end;

	start = assign_int_point(0, 0);
	end = assign_int_point(win->map.wide * 25 + 10, win->map.lenght * 50 + 21);
	cub_drawer(win->img, start, end, floor);
	start = assign_int_point(0, win->map.wide * 25 + 9);
	end = assign_int_point(win->map.wide * 25 + 11, win->map.lenght * 50 + 21);
	cub_drawer(win->img, start, end, ceiling);
}

void	draw_mini_map(t_window *win, char **matrix)
{
	t_cord	cord;
	t_point	start;
	t_point	end;

	cord.x = -1;
	cord.y = -1;
	start = assign_int_point(0, 0);
	end = assign_int_point(win->map.wide * 10 + 4, win->map.lenght * 10 + 4);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_int_point(10, 10);
	while (++cord.x < win->map.wide)
	{
		cord.y = -1;
		while (++cord.y < win->map.lenght)
		{
			start = assign_int_point(cord.y * 10 + 2, cord.x * 10 + 2);
			if (matrix[cord.x][cord.y] == '1')
				cub_drawer(win->img, start, end, 0x09005EFF);
			else if ((matrix[cord.x][cord.y] != ' '
				&& matrix[cord.x][cord.y] != '\n') || !matrix[cord.x][cord.y])
				cub_drawer(win->img, start, end, 0xB8A649FF);
		}
	}
	player_drawer(win, win->player->p, 0xFF322BFF);
}
