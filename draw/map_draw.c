/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 04:28:17 by ohachami          #+#    #+#             */
/*   Updated: 2023/09/28 04:28:20 by ohachami         ###   ########.fr       */
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
		if(pk.x > 0 && pk.y > 0)
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
			//ft_printf("%d-%d ",start.x + j, start.y + i);
			mlx_put_pixel(img, start.x + j, start.y + i, color);
			j++;
		}
		i++;
	}
}

t_point	player_drawer(t_window *win, t_point pos, double angle, int color)
{
	int		r;
	double	deg;

	r = -1;
	if (pos.x < 10)
		pos.x = win->map.lenght * 50;
	else if (pos.x > win->map.lenght * 50)
		pos.x = 11;
	if (pos.y < 10)
		pos.y = win->map.wide * 50;
	else if (pos.y > win->map.wide * 50)
		pos.y = 11;
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
	deg = angle;
	return (pos);
}

t_segm	wall(double sx, double sy, double ex, double ey)
{
	t_segm	wall;

	wall.end.x = ex;
	wall.end.y = ey;
	wall.start.x = sx;
	wall.start.y = sy;
	return (wall);
}

t_vector	rotation_vect(t_vector vect, double deg)
{
	t_vector	new_vect;

	new_vect.x = vect.y * sin(deg) + vect.x * cos(deg);
	new_vect.y = vect.y * cos(deg) - vect.x * sin(deg);
	if(new_vect.y < 0.00000000000001
		&& new_vect.y > -0.0000000000001)
		new_vect.y = 0;
	if(new_vect.x < 0.00000000000001
		&& new_vect.x > -0.0000000000001)
		new_vect.x = 0;
	return (new_vect);
}

double	dot_vect(t_vector vect, int n,  t_vector vect2)
{
	double	dot;

	if( n == 1)
		dot = vect.y * vect2.y + vect.x * vect2.x;
	else
		dot = vect.y * vect2.y - vect.x * vect2.x;
	//printf(")v.x=%.2f,.,v.y=%.2f,     dot=%.2f(        v2.x=%.2f,v2.y=%.2f\n",vect.x, vect.y, dot, vect2.x, vect2.y);
	return (dot);
}

t_vector	assign_vect(double x, double y, t_point pos)
{
	t_vector	vec;

	vec.x = x - pos.x;
	vec.y = y - pos.y;
	return(vec);
}

t_segm *find_wall()
{
	t_segm	*edge = NULL;
	return(edge);
}

double	raycast(t_window *win, char **matrix, t_point *pos, t_vector v)
{
	int		i;
	int		j;
	t_point	step;
	t_point	a;
	t_point	unite;

	i = (win->player.p.x - 2) / 10;
	j = (win->player.p.y - 2) / 10;
	step.x = (v.x >= 0) - (v.x < 0);
	step.y = (v.y >= 0) - (v.y < 0);
	a.x = (v.x < 0) * ((i * 10 + 12 - win->player.p.x) - (v.x >= 0) * (win->player.p.x - i * 10 - 2)) / 10;
	a.y = (v.x < 0) * ((j * 10 + 12 - win->player.p.y) - (v.y >= 0) * (win->player.p.y - j * 10 - 2)) / 10;
	unite.x = sqrt(1 + pow(v.y / v.x,2)) * a.x;
	unite.y = sqrt(1 + pow(v.x / v.y,2)) * a.y ;
	if((v.y > -0.0001 && v.y < 0.0001) || (v.x > -0.0001 && v.x < 0.0001))
	{
		unite = assign_point(a.x, a.y);
		while (matrix[j][i] != '1')
		{
			if ((v.x < -0.0001 || v.x > 0.0001))
			{
				i += step.x;
				unite.x += 1;
			}
			if ((v.y < -0.0001 || v.y > 0.0001))
			{
				j += step.y;
				unite.x += 1;
			}
		}
	}
	else
	{
	//printf("================================ m = %f \n", s.x);
	printf("u.y = %f u.x = %f m[%i][%i] step.x=%.3f y=%.3f\n", unite.y, unite.x, j, i, a.x, a.y);
	while (matrix[j][i] != '1')
	{
		if (unite.x < unite.y)
		{
			i += step.x;
			unite.x += sqrt(1 + pow(v.y / v.x,2));
		}
		else
		{
			j += step.y;
			unite.y += sqrt(1 + pow(v.x / v.y,2));
		}
		printf("u.y = %f u.x = %f m[%i][%i]\n", unite.y, unite.x, j, i);
	}
	}
	t_point	start;
	t_point	end = assign_int_point(4, 4);
	t_point r = assign_point(pos->x + 100 * v.x, pos->y + 100 * v.y);
	draw_line(win, win->player.p, r);
	start = assign_int_point(i * 10 + 5, j * 10 + 5);
	cub_drawer(win->img, start, end, 0x09FFFFFF);
	return((unite.x <= unite.y) * unite.y + (unite.x > unite.y) * unite.x);
}
/*
t_point	raycast(t_window *win, char **matrix, t_point *pos, t_vector v)
{
	t_point		r;
	t_segm		edge;
	double		t;
	double		d;

	d = 0;
	t = 0;
	r = assign_point(win->map.lenght * 10 + 4 + pos->x, win->map.wide * 10 + 4 + pos->y);
	if (!v.x && !v.y)
		return (assign_point(0, 0));
	edge = find_wall(win, matrix, v);
	d = (edge.end.y - edge.start.y) * v.x - (edge.end.x - edge.start.x) * v.y;
	d = ((pos->y - edge.start.y) * v.x - (pos->x - edge.start.x) * v.y) / d;
	if (v.x)
		t = ((1 - d) * edge.start.x + d * edge.end.x - pos->x) / v.x;
	else if (v.y)
		t = ((1 - d) * edge.start.y + d * edge.end.y - pos->y) / v.y;
	if (d >= 0 && d <= 1 && t >= 0 )
		r = assign_point(pos->x + t * v.x, pos->y + t * v.y);
	//draw_line(win, *pos, r);
	return (r);
}*/

// uwu

t_vector	ft_draw_map(t_window *win, char **matrix, t_point *pos, t_vector v)
{
	int			i;
	int			j;
	t_point		start;
	t_point		end;
	//t_vector	uv;

	i = -1;
	j = -1;
	start = assign_int_point(0, 0);
	end = assign_int_point(win->map.wide * 10 + 50, win->map.lenght * 10 + 4);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_int_point(10, 10);
	while (++i < win->map.wide)
	{
		j = -1;
		while (++j < win->map.lenght)
		{
			start = assign_int_point(j * 10 + 2, i * 10 + 2);
			if (matrix[i][j] == '1')
				cub_drawer(win->img, start, end, 0x09005EFF);
			else if ((matrix[i][j] != ' ' && matrix[i][j] != '\n')
				|| !matrix[i][j])
				cub_drawer(win->img, start, end, 0xB8A649FF);
		}
	}
	//if (check_inside(win, pos))
		win->player.p = player_drawer(win, *pos, win->player.angle, 0xFF322BFF);
	//else
	//	win->player.p = player_drawer(win, win->player.p, win->player.angle, 0xFF322BFF);
	//ft_printf("ok %d\n", check_inside(win, pos));
	if (check_inside(win, pos))
	{
		//lv = rotation_vect(lv, angle_adjast(win->player.angle, '*') + M_PI / 10);
		//raycast(win, win->edge, pos, lv);
		raycast(win, matrix, pos, v);
		//printf("ux=%.2f,.,uy=%.2f",uv.x, uv.y);
		//printf("lx=%.2f,.,ly=%.2f\n",uv.x, uv.y);
		/*i = 0;
		j = 0;
		//printf(")x=%.2f,.,y=%.2f,     a=%.2f(\n",v.x, v.y, angle_adjast(win->player.angle + M_PI / 15, '*'));
		while (win->edge[i].end.x > -1)
		{
			v.x = win->edge[i].start.x - pos->x;
			v.y = win->edge[i].start.y - pos->y;
			if (dot_vect(rotation_vect(lv, M_PI / 2), v) < 0 && dot_vect(rotation_vect(uv, M_PI / 2), v) > 0)
				win->rays[j] = raycast(win, win->edge, pos, v);
			v.x = win->edge[i].end.x - pos->x;
			v.y = win->edge[i].end.y - pos->y;
			if (dot_vect(rotation_vect(lv, M_PI / 2), v) < 0 && dot_vect(rotation_vect(uv, M_PI / 2), v) > 0)
				win->rays[j + 1] = raycast(win, win->edge, pos, v);
			v.x = win->edge[i + 3].end.x - pos->x;
			v.y = win->edge[i + 3].end.y - pos->y;
			if (dot_vect(rotation_vect(lv, M_PI / 2), v) < 0 && dot_vect(rotation_vect(uv, M_PI / 2), v) > 0)
				win->rays[j + 2] = raycast(win, win->edge, pos, v);
			v.x = win->edge[i + 3].start.x - pos->x;
			v.y = win->edge[i + 3].start.y - pos->y;
			if (dot_vect(rotation_vect(lv, M_PI / 2), v) < 0 && dot_vect(rotation_vect(uv, M_PI / 2), v) > 0)
				win->rays[j + 3] = raycast(win, win->edge, pos, v);
			j += 4;
			i += 4;
		}*/
	}
	return (v);

}
/*
void	ft_draw_scene(t_window *win, t_point *pos, t_vector lv)
{
		int	n;
		int	i;
		int	j;

		i = 0;
		j = win->walls_num;
		while(--j > 1)
		{
			while(++i < j)
			{
				if(comp_rays(win->rays[i], lv, *pos) > comp_rays(win->rays[i - 1], lv, *pos))
				{
					n = win->rays[i].x;
					win->rays[i].x = win->rays[i - 1].x;
					win->rays[i - 1].x = n;

					n = win->rays[i].y;
					win->rays[i].y = win->rays[i - 1].y;
					win->rays[i - 1].y = n;
				}
			}
			i = 0;
		}
		i = -1;
		j = 200;
		while(++j < 300)
		{
			i = -1;
			while(++i < 20)
			{
				mlx_put_pixel(win->mini_map, i +300, j, 0xFF322BFF);
			}
		}
		while(win->rays[++i].x > 0)
		{
			printf("ray[%d].x=%.2f,y=%.2f| ",i, win->rays[i].x, win->rays[i].y);
		}
		//printf("\n");

		double dis;
		while (++i)
		{
			dis = 0;
			v = rotation_vect(uv, M_PI / 720 * i);
			if (dot_vect(rotation_vect(lv, M_PI / 2), v) >= 0 || dot_vect(rotation_vect(uv, M_PI / 2), v) <= 0)
				break;
			end = raycast(win, edge, pos, v);
			dis = sqrt(pow(pos->x - end.x, 2) + pow(pos->y - end.y, 2)) * 4;
			j = 0;
			while(++j < (int)dis)
			{
				mlx_put_pixel(win->img, i + 200, j, 0x5091903F);
			}
		}*/
//}
