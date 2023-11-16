/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:58:11 by sbellafr          #+#    #+#             */
/*   Updated: 2023/09/03 00:44:01 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// static void ft_error(void)
//
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void free_all(t_window *win, char **elem)
{
	int j;

	j = -1;
	while (elem[++j])
	{
		free(elem[j]);
	}
	free(elem);
	if(win->img)
		mlx_delete_image(win->mlx_ptr, win->img);
	if(win->mlx_ptr)
		mlx_terminate(win->mlx_ptr);
	free(win->player);
	free(win->screen);
	free(win);
	//system("leaks $(ps | grep cub3D | awk '{if (NR==1) print$1}')");
}

void ft_start(t_map *g)
{
	t_window *win;
	win = (t_window *)ft_calloc(1, sizeof(t_window));
	win->screen = (t_cord *)ft_calloc(1, sizeof(t_cord));

	win->screen->x = 1280;
	win->screen->y = 720;
	win->player = g->player;
	win->map = g;
	win->map->wide = g->wide;
	win->map->len = g->len;
	//printf("a=[%d][%d]%f",win->map->wide, win->map->len, win->player->angle / M_PI *180);
	win->t.ea = mlx_load_png(g->ea);
	win->t.so = mlx_load_png(g->so);
	win->t.no = mlx_load_png(g->no);
	win->t.we = mlx_load_png(g->we);
	win->t.ceileng = get_color(g->c, 0, 0, 0);
	win->t.floor = get_color(g->f, 0, 0, 0);
	if(!win->t.ea || !win->t.so || !win->t.we || !win->t.no 
		|| !win->t.ceileng || !win->t.floor)
	{
		free_all(win, win->map->mapo);
		printf("error\n");
		exit(1);
	}
	printf("color floor = #%X ceileng = #%X\n",win->t.floor, win->t.ceileng);
	
	free(g->ea);
	free(g->so);
	free(g->no);
	free(g->we);
	free(g->c);
	free(g->f);
	init_val(win);
	free_all(win, win->map->mapo);
}

