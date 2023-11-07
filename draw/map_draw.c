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

void texture_to_img(mlx_texture_t* texture, mlx_image_t *img, t_window *win)
{
	uint32_t 		y;
	uint32_t 		x;
	uint8_t*	pixelx;
	uint8_t*	pixeli;

	(void)(win);
	y = -1;
	x = 0;
	while (++y < texture->height)
	{
		x = -1;
		while (++x < texture->width)
		{
			if (((y * texture->width) + x) < (unsigned int) (win->map.wide * 50 * win->map.lenght * 50))
			{
				pixelx = &texture->pixels[((y * texture->width) + x) * texture->bytes_per_pixel];
				pixeli = &img->pixels[((y * img->width) + x) * texture->bytes_per_pixel];
				ft_memmove(pixeli, pixelx, texture->bytes_per_pixel);
			}
		}
	}
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
		step = fabs(dp.x);
	else
		step = fabs(dp.y);
	i = -1;
	while (++i < step)
	{
	//ft_printf("x=%d,.,y=%d\n",(int)pk.x, (int)pk.y);
		if (pk.x > 0 && pk.y > 0)
			mlx_put_pixel(win->mini_map, pk.x, pk.y, 0xFF322BFF);
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
			mlx_put_pixel(win->mini_map, pos.x + r * cos(deg),
				pos.y + r * sin(deg), color);
			deg += M_PI / 180;
		}
	}
}

t_segm	wall(t_cord cord, t_window *win, t_point step, int is_it_x)
{
	t_segm	wall;

	if (is_it_x < 0)
	{
		wall.end = assign_point(win->map.lenght * 10, cord.j * 10 + 12);
		wall.start = assign_point(10, cord.j * 10 + 12);
		if (step.y > 0)
		{
			wall.end = assign_point(win->map.lenght * 10, cord.j * 10 + 2);
			wall.start = assign_point(10, cord.j * 10 + 2);
		}
	}
	else
	{
		wall.end = assign_point(cord.i * 10 + 12, win->map.wide * 10);
		wall.start = assign_point(cord.i * 10 + 12, 10);
		if (step.x > 0)
		{
			wall.end = assign_point(cord.i * 10 + 2, win->map.wide * 10);
			wall.start = assign_point(cord.i * 10 + 2, 10);
		}
	}
	return (wall);
}

double	dot_vect(t_vector vect ,t_vector vect2)
{
	double	dot;

	dot = vect.y * vect2.y + vect.x * vect2.x;
	//printf(")v.x=%.2f,.,v.y=%.2f,     dot=%.2f(        v2.x=%.2f,v2.y=%.2f\n",vect.x, vect.y, dot, vect2.x, vect2.y);
	return (dot);
}

double	norme_vect(t_vector vect)
{
	double	norme;

	norme = sqrt(pow(vect.x, 2) + pow(vect.y, 2));
	//printf(")v.x=%.2f,.,v.y=%.2f,     dot=%.2f(        v2.x=%.2f,v2.y=%.2f\n",vect.x, vect.y, dot, vect2.x, vect2.y);
	return (norme);
}

t_point	contact_p(t_window *win, t_segm edge, t_point pos, t_vector v)
{
	t_point	r;
	double	t;
	double	d;

	d = 0;
	t = 0;
	//printf("================================ start.x= %.0f start.y= %.0f end.x= %.0f end.y= %.0f\n", edge.start.x, edge.start.y,  edge.end.x, edge.end.y);
	r = assign_point(win->map.lenght * 10 + 4 + pos.x,
			win->map.wide * 10 + 4 + pos.y);
	if (!v.x && !v.y)
		return (assign_point(0, 0));
	d = (edge.end.y - edge.start.y) * v.x - (edge.end.x - edge.start.x) * v.y;
	d = ((pos.y - edge.start.y) * v.x - (pos.x - edge.start.x) * v.y) / d;
	if (v.x)
		t = ((1 - d) * edge.start.x + d * edge.end.x - pos.x) / v.x;
	else if (v.y)
		t = ((1 - d) * edge.start.y + d * edge.end.y - pos.y) / v.y;
	if (d >= 0 && d <= 1 && t >= 0)
		r = assign_point(pos.x + t * v.x, pos.y + t * v.y);
	draw_line(win, pos, r);
	return (r);
}

//t_ray	raycast(t_window *win, char **matrix, t_vector v, t_vector dir_v)
t_ray	raycast(t_window *win, char **matrix, t_vector v)
{
	t_cord	cord;
	int		side;
	t_point	step;
	t_point	a;
	t_point	dist;
	t_point	unite;

	cord.i = (win->player->p.x - 2) / 10;
	cord.j = (win->player->p.y - 2) / 10;
	step.x = (v.x >= 0) - (v.x < 0);
	step.y = (v.y >= 0) - (v.y < 0);
	if (v.x > 0)
		a.x = (cord.i * 10 + 12 - win->player->p.x) / 10;
	else
		a.x = (win->player->p.x - cord.i * 10 - 2) / 10;
	if (v.y > 0)
		a.y = (cord.j * 10 + 12 - win->player->p.y) / 10;
	else
		a.y = (win->player->p.y - cord.j * 10 - 2)  / 10;
	unite.x = fabs(a.x / v.x);
	unite.y = fabs(a.y / v.y);
	dist = assign_int_point(a.x - fabs(1 / v.x), a.y - fabs(1 / v.y));
	//printf("u.y = %f u.x = %f m[%i][%i] a.x=%.3f y=%.3f\n", unite.y, unite.x, cord.j, cord.i, a.x, a.y);
	while (matrix[cord.j][cord.i] != '1')
	{
		if (unite.x < unite.y || (v.y < 0.00001 && v.y > -0.00001))
		{
			cord.i += step.x;
			unite.x += fabs(1 / v.x);
			side = 1;
		}
		else if (unite.x >= unite.y || (v.x < 0.00001 && v.x > -0.00001))
		{
			cord.j += step.y;
			unite.y += fabs(1 / v.y);
			side = -1;
		}
		//printf("u.y = %f u.x = %f m[%i][%i]\n", unite.y, unite.x, cord.j, cord.i);
	}
	/*t_point	start;
	t_point	end = assign_int_point(4, 4);
	t_point r = assign_point(win->player.p.x + 100 * v.x, win->player.p.y + 100 * v.y);
	draw_line(win, win->player.p, r);
	start = assign_int_point(i * 10 + 5, j * 10 + 5);
	cub_drawer(win->img, start, end, 0x09FFFFFF);*/
	t_ray r;
	t_segm edge = wall(cord, win, step, side);
	/*if(side > 0)
		return((unite.x - a.x) * 10);
	else
		return((unite.y - a.y) * 10);*/
	if(side > 0 && edge.end.x > win->player->p.x)
		r.side = 's';
	else if(side > 0 && edge.end.x <= win->player->p.x)
		r.side = 'n';
	else if(side < 0 && edge.end.y < win->player->p.y)
		r.side = 'e';
	else
		r.side = 'w';
	r.p = contact_p(win, edge, win->player->p, v);
	//r.distance = sqrt(pow(r.p.x - win->player->p.x, 2) + pow(r.p.y - win->player->p.y, 2));
	//(dot_vect(dir_v, v))/ sqrt(v.x * v.x + v.y * v.y);
	//printf("plane [%f][%c]\n", r.distance, r.side);
	return(r);// * dot_vect(win->player->v, 1, v));

}

t_vector	add_vect(t_vector v1, t_vector v2)
{
	t_vector new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	return (new_v);
}

t_vector	ft_draw_map(t_window *win, char **matrix, t_point next_pos, t_vector v)
{
	int		i;
	int		j;
	t_point	start;
	t_point	end;

	//double f;
	start = assign_int_point(0, 0);
	end = assign_int_point(win->map.wide * 25 + 10, win->map.lenght * 50 + 21);
	cub_drawer(win->mini_map, start, end, 0x50dc0a50);
	start = assign_int_point(0, win->map.wide * 25 + 9);
	end = assign_int_point(win->map.wide * 25 + 11,  win->map.lenght * 50 + 21);
	cub_drawer(win->mini_map, start, end, 0x50001EE1);

	double		plane;
	t_ray		r;
	t_vector	nv;
	t_vector	add_v;
	next_pos = pos_adjast(win, next_pos);
	if (check_inside(win, next_pos))
	{
		//lv = rotation_vect(lv, angle_adjast(win->player.angle, '*') + M_PI / 10);
		win->player->p = assign_point(next_pos.x, next_pos.y);
		plane = -1;
		i = -1;
		while (++i < win->map.lenght * 50 + 20)
		{
			//printf("%p\n",win->texture);
			plane = (2 * (double)i / 20 - 1) * M_PI / (double)180;
			add_v.y = 0;
			add_v.x = 1;
			nv = rotation_vect(add_v, angle_adjast(win->player->angle + plane, '*'));
			//nv = add_vect(add_v, v);
			r = raycast(win, matrix, nv);
			//r.distance = sqrt(pow(r.p.x - win->player->p.x, 2) + pow(r.p.y - win->player->p.y, 2)) * cos(angle_adjast(win->player->angle - plane, '*'));
			r.distance = sqrt(pow(r.p.x - win->player->p.x, 2) + pow(r.p.y - win->player->p.y, 2));
			//printf("disctance==[%.4f][]\n", plane);
			j = ((win->map.wide * 50 + 20) - (win->map.wide * 50 + 20)/ r.distance * 10) / 2;
			while (++j < ((win->map.wide * 50 + 20) + (win->map.wide * 50 + 20) / r.distance * 10 ) / 2)
			{
				if (j < win->map.wide * 50 + 20 && j > 0)
					mlx_put_pixel(win->mini_map, i, j, 0x5091903F);
				texture_to_img(win->texture, win->mini_map, win);
			}
			// sigfault in next_pos==[247.4636][44.6134] v.x=0.013084, v.y=0.249657 angle=4.76
		}
	}

	
	
	i = -1;
	j = -1;
	start = assign_int_point(0, 0);
	end = assign_int_point(win->map.wide * 10 + 4, win->map.lenght * 10 + 4);
	cub_drawer(win->mini_map, start, end, 0x909090FF);
	end = assign_int_point(10, 10);
	while (++i < win->map.wide)
	{
		j = -1;
		while (++j < win->map.lenght)
		{
			start = assign_int_point(j * 10 + 2, i * 10 + 2);
			if (matrix[i][j] == '1')
				cub_drawer(win->mini_map, start, end, 0x09005EFF);
			else if ((matrix[i][j] != ' ' && matrix[i][j] != '\n')
				|| !matrix[i][j])
				cub_drawer(win->mini_map, start, end, 0xB8A649FF);
		}
	}
	player_drawer(win, win->player->p, 0xFF322BFF);
	draw_line(win, win->player->p, r.p);
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
			dis = sqrt(pow(pos.x - end.x, 2) + pow(pos.y - end.y, 2)) * 4;
			j = 0;
			while(++j < (int)dis)
			{
				mlx_put_pixel(win->img, i + 200, j, 0x5091903F);
			}
		}*/
//}
