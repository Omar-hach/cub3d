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

double	angle_adjast(double angle, char sign)
{
	if (angle <= 0)
		angle = M_PI * 2;
	if (sign == '-')
		angle -= M_PI / 180;
	if (sign == '+')
		angle += M_PI / 180;
	if (angle > M_PI * 2)
		angle = M_PI / 180;
	return (angle);
}

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
		step = fabs(dp.x) ;
	else
		step = fabs(dp.y);
	i = -1;
	while (++i < step)
	{
	//ft_printf("x=%d,.,y=%d\n",(int)pk.x, (int)pk.y);
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
/*
t_point	player_drawer(mlx_image_t *img, t_point pos, t_player player, int color)
{
	int		r;
	float	deg;

	r = -1;
	deg = 0;
	if (player.p.x != 0 || player.p.y != 0)
		pos = player.p;
	while (++r < 25)
		mlx_put_pixel(img, pos.x + 25 + r, pos.y + 25 + r, color);
	r = 0;
	while (r < 11)
	{
		deg = 0;
		while (deg < M_PI * 2)
		{
			mlx_put_pixel(img, pos.x + 25 + r * cos(deg),
				pos.y + 25 + r * sin(deg), color);
			deg += M_PI / 180;
		}
		r++;
	}
	return (pos);
}*/

t_point	player_drawer(t_window *win, t_point pos, double angle, int color)
{
	int		r;
	double	deg;

	r = -1;
	pos.x = (win->map.lenght * 50 + 10) * (pos.x < 1)
		+ pos.x * (pos.x <= win->map.lenght * 50 + 20);
	pos.y = (pos.y < 1) * (win->map.wide * 50 + 10)
		+ pos.y * (pos.y <= win->map.wide * 50 + 20);
	r = 0;
	deg = 0;
	while (r < 11)
	{
		deg = 0;
		while (deg < M_PI * 2)
		{
			mlx_put_pixel(win->img, pos.x + r * cos(deg),
				pos.y + r * sin(deg), color);
			deg += M_PI / 180;
		}
		r++;
	}
	deg = angle;
	return(pos);
}

t_segm	wall(double sx, double sy, double ex, double ey)
{
	t_segm wall;

	wall.end.x = ex;
	wall.end.y = ey;
	wall.start.x = sx;
	wall.start.y = sy;
	return (wall);
}

t_vector	rotation_vect(t_vector vect, double deg)
{
	t_vector new_vect;

	new_vect.y = vect.y * cos(deg) - vect.x * sin(deg);
	new_vect.x = vect.y * sin(deg) + vect.x * cos(deg);
	/*if(new_vect.y <= -0.000000)
		new_vect.y = 0;
	if(new_vect.x <= -0.000000)
		new_vect.x = 0;*/
	return (new_vect);
}
int	dot_vect(t_vector vect, t_vector vect2)
{
	int dot;

	dot = vect.y * vect2.y + vect.x * vect2.y;
	return (dot);
}

void printooo(double lol)
{
	printf("|%.1f|\n",lol);
}

int	raycast(t_window *win, t_segm *edge, t_point *pos, double deg)
{
	t_vector v;
	//t_vector n;
	t_point r;
	double t;
	double d;
	int i;

	i = 7;
	d = 0;
	t = 0;
	v.x = 1;
	v.y = 0;
	v = rotation_vect(v, deg);
	//printf("x=%0.2f|y=%0.2f\n",pos->x,pos->y);
	while (i > -1)
	{
		if (!v.x && !v.y)
			break ;
		d = (edge[i].end.y - edge[i].start.y) * v.x - (edge[i].end.x - edge[i].start.x) * v.y;
		if (d < 0.00000000000001 && d > -0.0000000000001)
		{
			i--;
			continue ;
		}
		d = ((pos->y - edge[i].start.y) * v.x - (pos->x - edge[i].start.x) * v.y) / d;
		if (v.x > 0.00000000000001 || v.x < -0.0000000000001){
			t = ((1 - d) * edge[i].start.x + d * edge[i].end.x - pos->x) / v.x;}
		else if (v.y > 0.0000000000001 || v.y < -0.0000000000001){
			t = ((1 - d) * edge[i].start.y + d * edge[i].end.y - pos->y) / v.y;}
		if (d >= 0 && d <= 1 && t >= 0)
			break ;
		i--;
		//n = rotation_vect(v, 90);
		//if(dot_vect(v, n))
		//	;
	}
	r = assign_point(pos->x + t * v.x, pos->y + t * v.y);
	draw_line(win, *pos, r);
	//printf("t=%.2f|r.x=%.2f|r.y=%.2f|\n",t,r.x,r.y);
	return (0);
}

void	ft_draw_map(t_window *win, char **matrix, t_point *pos)
{
	int		i;
	int		j;
	t_point	start;
	t_point	end;

	i = -1;
	j = -1;
	start = assign_point(0, 0);
	end = assign_point(win->map.wide * 50 + 20, win->map.lenght * 50 + 20);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_point(50, 50);
	while (++i < win->map.wide)
	{
		j = -1;
		while (++j < win->map.lenght)
		{
			start = assign_point(j * 50 + 10, i * 50 + 10);
			if (matrix[i][j] == '1')
				cub_drawer(win->img, start, end, 0x09005EFF);
			else if ((matrix[i][j] != ' ' && matrix[i][j] != '\n')
				|| !matrix[i][j])
				cub_drawer(win->img, start, end, 0xB8A649FF);
		}
	}
	if(check_inside(win, pos))
		win->player.p = player_drawer(win, *pos, win->player.angle, 0xFF322BFF);
	else
		win->player.p = player_drawer(win, win->player.p, win->player.angle, 0xFF322BFF);
	t_segm *edge = (t_segm *)ft_calloc(9,sizeof(t_segm));
	edge[0] = wall(60, 60, 560, 60);
	edge[1] = wall(60, 60, 60, 360);
	edge[3] = wall(60, 360, 560, 360);
	edge[2] = wall(560, 60, 560, 360);
	edge[4] = wall(50 * 8 + 10, 50 * 5 + 10, 50 * 8 + 10, 50 * 6 + 10);
	edge[5] = wall(50 * 8 + 10, 50 * 5 + 10, 50 * 9 + 10, 50 * 5 + 10);
	edge[6] = wall(50 * 8 + 10, 50 * 6 + 10, 50 * 9 + 10, 50 * 6 + 10);
	edge[7] = wall(50 * 9 + 10, 50 * 5 + 10, 50 * 9 + 10, 50 * 6 + 10);
	edge[8] = wall(-1, -1, -1, -1);
	raycast(win, edge, pos, win->player.angle);
	//printf(" x=%d,y=%d|a=%f ",win->player.p.x, win->player.p.y, win->player.angle);
	free(edge);
	edge = NULL;
}
