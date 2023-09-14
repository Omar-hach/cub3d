/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:16:33 by ohachami          #+#    #+#             */
/*   Updated: 2023/09/14 19:16:35 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	angle_adjast(int angle, char sign)
{
	if(angle <= 0)
		angle = 360;
	if(sign == '-')
		angle--;
	if(sign == '+')
		angle++;
	if(angle > 360)
		angle = 1;
	return(angle);
}

void	draw_line(t_window *win, t_point start, t_point end)
{
	t_point	line;
	float	big;
	t_point	steps;
	t_point	pixels;
	int		i;

	i = 0;
	line.x = end.x - start.x;
	line.y = end.y - start.y;
	if (abs(line.x) > abs(line.y))
		big = abs(line.x);
	else
		big = abs(line.y);
	steps.x = line.x / big;
	steps.y = line.y / big;
	pixels = start;
	while (i < big)
	{
		printf("y=%d x=%d\n", (int)pixels.y / 50, (int)pixels.x / 50);
		printf("y=%d x=%d\n", (int)start.y, (int)start.x);
		if (win->map.elem[(int)pixels.x / 50][(int)pixels.y / 50] == '1') // the problem is here pixels.y overflow
			break ;
		mlx_put_pixel(win->img, (int)pixels.x, (int)pixels.y, 0x1100FFff);
		pixels.x += steps.x;
		pixels.y += steps.y;
		i++;
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

t_point	player_drawer(mlx_image_t *img, t_point pos, t_player player,  int color)
{
	int	r;
	float deg;

	r = -1;
	deg = 0;
	if(player.p.x != 0 || player.p.y != 0)
		pos = player.p;
	while(++r < 25)
		mlx_put_pixel(img, pos.x + 25 ,pos.y + 25 + r, color);
	r = 0;
	while(r < 11)
	{
		deg = 0;
		while (deg < M_PI * 2)
		{
			mlx_put_pixel(img, pos.x + 25 + r * cos(deg),
				pos.y + 25 + r * sin(deg), color);
			deg +=  M_PI / 180;
		}
		r++;
	}
	return(pos);
}

/*
t_point	player_drawer(mlx_image_t *img, t_point pos, t_player player,  int color)
{
	int	r;
	float deg;

	r = -1;
	deg = angle_adjast(player.angle, '+');
	if(player.p.x != 0 || player.p.y != 0)
		pos = player.p;
	while(++r < 25)
		mlx_put_pixel(img, pos.x + 25 ,pos.y + 25 + r, color);
	r = 0;
	while(r < 11)
	{
		deg = angle_adjast(player.angle, '+');
		mlx_put_pixel(img, pos.x + 25 + r * cos(deg),
				pos.y + 25 + (r) * sin(deg++), color);
		while (deg < M_PI * 2)
		{
			mlx_put_pixel(img, pos.x + 25 + r * cos(deg),
				pos.y + 25 + r * sin(deg), color);
			deg +=  M_PI / 180;
		}
		r++;
	}
	return(pos);
}*/

void	ft_draw_map(t_window *win, char **matrix, t_player *player)
{
	int		i;
	int		j;
	t_point	start;
	t_point	end;

	i = -1;
	j = -1;
	start = assign_point(0, 0, 0);
	end = assign_point(win->map.wide * 50 + 20, win->map.lenght * 50 + 20, 0);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_point(50, 50, 0);
	while (++i < win->map.wide)
	{
		j = -1;
		while (++j < win->map.lenght)
		{
			start = assign_point(j * 50 + 10, i * 50 + 10, 0);
			if (matrix[i][j] == '1')
				cub_drawer(win->img, start, end, 0x09005EFF);
			else if ((matrix[i][j] != ' ' && matrix[i][j] != '\n') ||  !matrix[i][j])
				cub_drawer(win->img, start, end, 0xB8A649FF);
		}
	}
	player->p = player_drawer(win->img, start, *player, 0xFF322BFF);
	//printf(" x=%d,y=%d|a=%f ",win->player.p.x, win->player.p.y, win->player.angle);
}

