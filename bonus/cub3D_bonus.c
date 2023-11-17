/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:34:37 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/13 10:34:39 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*void mouse_b(double xpos, double ypos, void* param)
{
	t_window *win;
	int x;
	int	y;

	win = (t_window *)param;
	if(xpos > 0 && xpos < win->screen->x && ypos > 0 && ypos < win->screen->y)
	{
		printf("pos[%f][%f]\n", xpos, ypos);
	}
}*/

void	init_val_b(t_window *win)
{
	win->screen->x = 1280;
	win->screen->y = 720;
	win->player->speed = 0.5;
	win->player->v.x = win->player->speed;
	win->player->v.y = 0;
	win->player->v = assign_vect(win->player->speed, 0, win->player->angle);
	win->t.ea = mlx_load_png("assets/m64 atlantic.png");
	win->t.so = mlx_load_png("assets/bowser_2.png");
	win->t.no = mlx_load_png("assets/bowser3.png");
	win->t.we = mlx_load_png("assets/egypt.png");
	win->mlx_ptr = mlx_init(win->screen->x, win->screen->y,
			"Super Duper Cool 3D Game!!!", false);
	if (!win->mlx_ptr)
		error();
	win->img = mlx_new_image(win->mlx_ptr,
			win->screen->x, win->screen->y);
	if (!win->img)
		error();
	mlx_loop_hook(win->mlx_ptr, &keyhook_b, win);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	mlx_loop(win->mlx_ptr);
}

void	ft_start_b(t_map *g)
{
	t_window	*win;

	win = (t_window *)ft_calloc(1, sizeof(t_window));
	win->screen = (t_cord *)ft_calloc(1, sizeof(t_cord));
	win->screen->x = 1280;
	win->screen->y = 720;
	win->player = g->player;
	win->map = g;
	win->map->wide = g->wide;
	win->map->len = g->len;
	win->t.ea = mlx_load_png(g->ea);
	win->t.so = mlx_load_png(g->so);
	win->t.no = mlx_load_png(g->no);
	win->t.we = mlx_load_png(g->we);
	win->t.ceileng = get_color(g->c, 0, 0, 0);
	win->t.floor = get_color(g->f, 0, 0, 0);
	if (!win->t.ea || !win->t.so || !win->t.we || !win->t.no 
		|| !win->t.ceileng || !win->t.floor)
	{
		free_all(win, win->map->mapo);
		printf("error=\n");
		exit(1);
	}
	printf("color floor = #%X ceileng = #%X\n", win->t.floor, win->t.ceileng);
	free(g->ea);
	free(g->so);
	free(g->no);
	free(g->we);
	free(g->c);
	free(g->f);
	init_val_b(win);
	free_all(win, win->map->mapo);
}

void	parser_b(t_map *g, int fd)
{
	int	error;
	int	i;

	error = 0;
	g->player = ft_calloc(1, sizeof(t_player));
	error += get_data(fd, g);
	error += get_map(fd, g);
	g->mapo = convert_map(g->map_line);
	g->full_file = convert_map(g->split_line);
	error += check_borders_line(g);
	error += check_borders_col(g);
	g->player = get_player_location(g->player, g, &i);
	error += get_text(g);
	error += check_map_line(g->mapo);
	get_len_wide(g);
	i = 0;
	printf("no = >%s-\n", g->so);
	printf("no = >%s-\n", g->no);
	printf("no = >%s-\n", g->ea);
	printf("no = >%s-\n", g->we);
	printf("no = >%s-\n", g->c);
	printf("no = >%s-\n", g->f);
	printf("----------------\t\n");
	while (g->mapo[i])
		printf("%s\n", g->mapo[i++]);
	if (!error)
		ft_start_b(g);
}

int main(int ac, char **av)
{
	t_map	*g;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (ac == 2 && fd > -1)
	{
		g = ft_calloc(1, sizeof(t_map));
		parser_b(g, fd);
	}
	else
	{
		ft_putstr_fd("no map", 2);
		return(1);
	}
}
