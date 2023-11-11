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

t_segm	wall(t_cord cord, t_window *win, t_point step, int is_it_x)
{
	t_segm	wall;

	if (is_it_x < 0)
	{
		wall.end = assign_point(win->map.lenght * 10, cord.y * 10 + 12);
		wall.start = assign_point(10, cord.y * 10 + 12);
		if (step.y > 0)
		{
			wall.end = assign_point(win->map.lenght * 10, cord.y * 10 + 2);
			wall.start = assign_point(10, cord.y * 10 + 2);
		}
	}
	else
	{
		wall.end = assign_point(cord.x * 10 + 12, win->map.wide * 10);
		wall.start = assign_point(cord.x * 10 + 12, 10);
		if (step.x > 0)
		{
			wall.end = assign_point(cord.x * 10 + 2, win->map.wide * 10);
			wall.start = assign_point(cord.x * 10 + 2, 10);
		}
	}
	return (wall);
}

double	dot_vect(t_vector vect ,t_vector vect2)
{
	double	dot;

	dot = vect.y * vect2.y + vect.x * vect2.x;
	return (dot);
}

double	norme_vect(t_vector vect)
{
	double	norme;

	norme = sqrt(pow(vect.x, 2) + pow(vect.y, 2));
	return (norme);
}


t_point	contact_p(t_window *win, t_segm edge, t_point pos, t_vector v)
{
	t_point	r;
	double	t;
	double	d;

	d = 0;
	t = 0;
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
	//printf("================================ t= %f ", t);
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

	cord.x = (win->player->p.x - 2) / 10;
	cord.y = (win->player->p.y - 2) / 10;
	step.x = (v.x >= 0) - (v.x < 0);
	step.y = (v.y >= 0) - (v.y < 0);
	if (v.x > 0)
		a.x = (cord.x * 10 + 12 - win->player->p.x) / 10;
	else
		a.x = (win->player->p.x - cord.x * 10 - 2) / 10;
	if (v.y > 0)
		a.y = (cord.y * 10 + 12 - win->player->p.y) / 10;
	else
		a.y = (win->player->p.y - cord.y * 10 - 2)  / 10;
	unite.x = fabs(a.x / v.x);
	unite.y = fabs(a.y / v.y);
	dist = assign_int_point(a.x - fabs(1 / v.x), a.y - fabs(1 / v.y));
	//printf("u.y = %f u.x = %f m[%i][%i] a.x=%.3f y=%.3f\n", unite.y, unite.x, cord.y, cord.x, a.x, a.y);
	while (cord.y < win->map.wide && cord.y >= 0 && cord.x < win->map.lenght && cord.x >= 0 && matrix[cord.y][cord.x] != '1')
	{
		if (unite.x < unite.y || (v.y < 0.00001 && v.y > -0.00001))
		{
			cord.x += step.x;
			unite.x += fabs(1 / v.x);
			side = 1;
		}
		else if (unite.x >= unite.y || (v.x < 0.00001 && v.x > -0.00001))
		{
			cord.y += step.y;
			unite.y += fabs(1 / v.y);
			side = -1;
		}
	}
	//printf("u.y = %f u.x = %f m[%i][%i]\n", unite.y, unite.x, cord.y, cord.x);
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


t_ray	draw_scene(t_window *win, char **matrix, t_point next_pos)
{
	double		plane;
	t_cord		cord;
	t_ray		r;
	t_vector	nv;
	t_vector	add_v;

	draw_background(win, 0x50dc0a50, 0x50001EE1);
	next_pos = pos_adjast(win, next_pos);
	cord.x = -1;
	cord.y = 0;
	win->player->p = assign_point(next_pos.x, next_pos.y);
	if (check_inside(win, next_pos))
	{
		plane = 0;
		while (++cord.x <= win->screen.x)
		{
			plane = (2 * (double)cord.x / 40 - 32) * M_PI / (double)180;
			add_v.x = 1 * win->player->speed;
			add_v.y = 0;
			nv = rotation_vect(add_v, angle_adjast(win->player->angle + plane, '*'));
			r = raycast(win, matrix, nv);
			r.distance = sqrt(pow(r.p.x - win->player->p.x, 2) + pow(r.p.y - win->player->p.y, 2)) * (dot_vect(win->player->v, nv) / (norme_vect(nv) * norme_vect(win->player->v)));
			//r.distance = sqrt(pow(r.p.x - win->player->p.x, 2) + pow(r.p.y - win->player->p.y, 2)) * cos(angle_adjast(plane, '*'));
			//printf("distance=%f ", r.distance);
			/*if(r.distance != 10)
				pause();*/
			//printf("v==[%.4f][%.4f] nv[%f][%f]\n", win->player->v.x, win->player->v.y,  nv.x, nv.y);
			//printf("distance=%f\n", r.distance);
			cord.y = (win->screen.y - win->screen.y / r.distance * 10) / 2 - 1; // 10 is the size of the cub
			/*if(cord.y < -1)
				cord.y = 0;
			if (cord.y > win->screen.y)
				cord.y = win->screen.y;*/
			//printf("cord==[%d][%d] ", cord.y, cord.x);
			texturess(win, r, cord);
		}
	}
	r = raycast(win, win->map.mapo, win->player->v);
	return (r);
}

