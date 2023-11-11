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

int	ft_color(int r, int g, int b)
{
	return (((r << 24) | (g << 16) | (b << 8) | 0xff));
}

double	dot_vect(t_vector vect, t_vector vect2)
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

t_ray	draw_scene(t_window *win, char **matrix, t_point next_pos)
{
	double		plane;
	t_cord		cord;
	t_ray		r;
	t_vector	nv;

	cord.x = -1;
	cord.y = 0;
	win->player->p = assign_point(next_pos.x, next_pos.y);
	r.p = win->player->p;
	if (check_inside(win, next_pos))
	{
		while (++cord.x < win->screen.x)
		{
			plane = (2 * (double)cord.x / 40 - 32) * M_PI / (double)180;
			nv = assign_vect(win->player->speed, 0,
					win->player->angle + plane);
			r = raycast(win, matrix, nv);
			r.distance = sqrt(pow(r.p.x - next_pos.x, 2) + pow(r.p.y - next_pos.y, 2))
				* (dot_vect(win->player->v, nv) / (norme_vect(nv) * norme_vect(win->player->v)));
			if (r.distance < 2)
				return (r);
			cord.y = (win->screen.y - win->screen.y / r.distance * 10) / 2 - 1; // 10 is the size of the cub
			texturess(win, r, cord);
		}
	}
	return (r);
}

//r.distance = sqrt(pow(r.p.x - win->player->p.x, 2) + pow(r.p.y - win->player->p.y, 2)) * cos(angle_adjast(plane, '*'));
