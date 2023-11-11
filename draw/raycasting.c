/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:35:29 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/11 09:35:31 by ohachami         ###   ########.fr       */
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
	return (r);
}

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
		a.y = (win->player->p.y - cord.y * 10 - 2) / 10;
	unite.x = fabs(a.x / v.x);
	unite.y = fabs(a.y / v.y);
	dist = assign_int_point(a.x - fabs(1 / v.x), a.y - fabs(1 / v.y));
	while (cord.y < win->map.wide && cord.y >= 0 && cord.x < win->map.lenght
		&& cord.x >= 0 && matrix[cord.y][cord.x] != '1')
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
	t_ray r;
	t_segm edge = wall(cord, win, step, side);
	if (side > 0 && edge.end.x > win->player->p.x)
		r.side = 's';
	else if (side > 0 && edge.end.x <= win->player->p.x)
		r.side = 'n';
	else if (side < 0 && edge.end.y < win->player->p.y)
		r.side = 'e';
	else
		r.side = 'w';
	r.p = contact_p(win, edge, win->player->p, v);
	return (r);
}