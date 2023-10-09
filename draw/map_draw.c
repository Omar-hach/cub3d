/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:16:33 by ohachami          #+#    #+#             */
/*   Updated: 2023/10/09 23:59:10 by sbellafr         ###   ########.fr       */
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
	if(pos.x < 10)
		pos.x = win->map.lenght * 50 ;
	else if(pos.x > win->map.lenght * 50)
		pos.x = 11;
	if(pos.y < 10)
		pos.y = win->map.wide * 50;
	else if(pos.y > win->map.wide * 50)
		pos.y = 11;
	deg = 0;
	while (++r < 11)
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
	if(new_vect.y < 0.00000000000001
		&& new_vect.y > -0.0000000000001)
		new_vect.y = 0;
	if(new_vect.x < 0.00000000000001
		&& new_vect.x > -0.0000000000001)
		new_vect.x = 0;
	return (new_vect);
}
double	dot_vect(t_vector vect, t_vector vect2)
{
	double dot;

	dot = vect.y * vect2.y + vect.x * vect2.x;
	//printf(")v.x=%.2f,.,v.y=%.2f,     dot=%.2f(        v2.x=%.2f,v2.y=%.2f\n",vect.x, vect.y, dot, vect2.x, vect2.y);
	return (dot);
}

t_point	raycast(t_window *win, t_segm *edge, t_point *pos, t_vector v)
{
	t_point r;
	double t;
	double d;
	int i;

	i = 0;
	d = 0;
	t = 0;
	r = assign_point(win->map.lenght * 50 + 20 + pos->x, win->map.wide * 50 + 20 + pos->y);
	while (edge[i].end.x > -1)
	{
		if (!v.x && !v.y)
			return (assign_point(0, 0));
		d = (edge[i].end.y - edge[i].start.y) * v.x - (edge[i].end.x - edge[i].start.x) * v.y;
		if (d < 0.00000000000001 && d > -0.0000000000001)
		{
			i++;
			continue ;
		}
		d = ((pos->y - edge[i].start.y) * v.x - (pos->x - edge[i].start.x) * v.y) / d;
		if (v.x)
			t = ((1 - d) * edge[i].start.x + d * edge[i].end.x - pos->x) / v.x;
		else if (v.y)
			t = ((1 - d) * edge[i].start.y + d * edge[i].end.y - pos->y) / v.y;
		if (d >= 0 && d <= 1 && t >= 0 && pow(t * v.x, 2) +
			pow(t * v.y, 2) < pow(r.x - pos->x,2) + pow(r.y - pos->y, 2))
				r = assign_point(pos->x + t * v.x, pos->y + t * v.y);
		i++;
	}
	draw_line(win, *pos, r);
	return (r);
}

double	comp_rays(t_point ray, t_vector lu, t_point pos)
{
	double			norm_vec;
	t_vector	vec;

	vec.x = ray.x - pos.x;
	vec.y = ray.y - pos.y;
	norm_vec = sqrt(vec.x * vec.x + vec.y * vec.y);
	return(dot_vect(vec, lu) / norm_vec);
}

void	ft_draw_map(t_window *win, char **matrix, t_point *pos)
{
	int		i;
	int		j;
	t_point	start;
	t_point	end;
    t_vector lv;
	t_vector uv;
	t_vector v;

	i = -1;
	j = -1;
	start = assign_point(0, 0);
	end = assign_point(win->map.wide * 50 + 20, win->map.lenght * 50 + 20);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_point(50, 50);
	while (matrix[++i])
	{
		j = 0;
		while (matrix[i][j])
		{
			start = assign_point(j * 50 + 10, i * 50 + 10);
			if (matrix[i][j] == '1')	
				cub_drawer(win->img, start, end, 0x09005EFF);
			else if (matrix[i][j] == '0' || matrix[i][j] == 'E' || matrix[i][j] == 'S' || matrix[i][j] == 'W'|| matrix[i][j] == 'N')
				cub_drawer(win->img, start, end, 0xB8A649FF);
			j++;
		}
	}
	
	if(check_inside(win, pos))
		win->player.p = player_drawer(win, *pos, win->player.angle, 0xFF322BFF);
	else
		win->player.p = player_drawer(win, win->player.p, win->player.angle, 0xFF322BFF);
	//ft_printf("ok\n");
	if(check_inside(win, pos))
	{
		t_segm *edge = (t_segm *)ft_calloc(13,sizeof(t_segm));
		edge[8] = wall(60, 60, 560, 60);
		edge[9] = wall(60, 60, 60, 360);
		edge[10] = wall(560, 60, 560, 360);
		edge[11] = wall(60, 360, 560, 360);

		edge[4] = wall(50 * 8 + 10, 50 * 5 + 10, 50 * 8 + 10, 50 * 6 + 10);
		edge[5] = wall(50 * 8 + 10, 50 * 5 + 10, 50 * 9 + 10, 50 * 5 + 10);
		edge[6] = wall(50 * 8 + 10, 50 * 6 + 10, 50 * 9 + 10, 50 * 6 + 10);
		edge[7] = wall(50 * 9 + 10, 50 * 5 + 10, 50 * 9 + 10, 50 * 6 + 10);

		edge[0] = wall(50 * 9 + 10, 110, 50 * 9 + 10, 160);
		edge[1] = wall(50 * 9 + 10, 110, 50 * 10 + 10, 110);
		edge[2] = wall(50 * 9 + 10, 160, 50 * 10 + 10, 160);
		edge[3] = wall(50 * 10 + 10, 110, 50 * 10 + 10, 160);
		edge[12] = wall(-1, -1, -1, -1);

		uv.x = 1;
		uv.y = 0;
		uv = rotation_vect(uv, angle_adjast(win->player.angle, '*') - M_PI / 15);
		raycast(win, edge, pos, uv);
		//printf("ux=%.2f,.,uy=%.2f",uv.x, uv.y);
		lv.x = 1;
		lv.y = 0;
		lv = rotation_vect(lv, angle_adjast(win->player.angle, '*') + M_PI / 15);
		//printf("lx=%.2f,.,ly=%.2f\n",uv.x, uv.y);
		raycast(win, edge, pos, lv);
		i = 0;
		j = 0;
		t_point *rays = (t_point *)ft_calloc(13,sizeof(t_point));
		//printf(")x=%.2f,.,y=%.2f,     a=%.2f(\n",v.x, v.y, angle_adjast(win->player.angle + M_PI / 15, '*'));
		while(edge[i].end.x > -1)
		{
			v.x = edge[i].start.x - pos->x;
			v.y = edge[i].start.y - pos->y;
			if(dot_vect(rotation_vect(lv, M_PI / 2), v) < 0 && dot_vect(rotation_vect(uv, M_PI / 2), v) > 0)
				rays[j] = raycast(win, edge, pos, v);
			
			v.x = edge[i].end.x - pos->x;
			v.y = edge[i].end.y - pos->y;
			if(dot_vect(rotation_vect(lv, M_PI / 2), v) < 0 && dot_vect(rotation_vect(uv, M_PI / 2), v) > 0)
				rays[j + 1] = raycast(win, edge, pos, v);
			
			v.x = edge[i + 3].end.x - pos->x;
			v.y = edge[i + 3].end.y - pos->y;
			if(dot_vect(rotation_vect(lv, M_PI / 2), v) < 0 && dot_vect(rotation_vect(uv, M_PI / 2), v) > 0)
				rays[j + 2] = raycast(win, edge, pos, v);

			v.x = edge[i + 3].start.x - pos->x;
			v.y = edge[i + 3].start.y - pos->y;
			if(dot_vect(rotation_vect(lv, M_PI / 2), v) < 0 && dot_vect(rotation_vect(uv, M_PI / 2), v) > 0)
				rays[j + 3] = raycast(win, edge, pos, v);

			j += 4;
			i += 4;
		}
		i = 0;
		j = 13;
		int		n;
		/*while(rays[j].x)
			j++;*/
		//printf(" j =%d\n",j);
		while(--j > 1)
		{
			while(++i < j)
			{
				if(comp_rays(rays[i], lv, *pos) > comp_rays(rays[i - 1], lv, *pos))
				{
					n = rays[i].x;
					rays[i].x = rays[i - 1].x;
					rays[i - 1].x = n;

					n = rays[i].y;
					rays[i].y = rays[i - 1].y;
					rays[i - 1].y = n;
					//printf("ok%.2f ", comp_rays(rays[i], lv, *pos));
				}
			}
			i = 0;
		}
		i = -1;
		/*while(rays[++i].x > 0)
			printf("rays[%d].x=%.2f .y=%.2f ",i,rays[i].x, rays[i].y);*/
		//printf(" x=%.2f,y=%d|a=%f ",win->player.p.x, win->player.p.y, win->player.angle);
		free(edge);
		edge = NULL;
	}
}