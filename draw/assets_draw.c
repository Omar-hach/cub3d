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
			if(start.x > -j && start.y > -i)
				mlx_put_pixel(img, start.x + j, start.y + i, color);
			j++;
		}
		i++;
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
