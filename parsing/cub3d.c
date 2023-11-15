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
	mlx_delete_image(win->mlx_ptr, win->img);
	mlx_terminate(win->mlx_ptr);
	free(win->player);
	free(win);
	//system("leaks $(ps | grep cub3D | awk '{if (NR==1) print$1}')");
}

// void get_player_location(t_player *player, char **mapo)
// {
// 	int i = 0;
// 	int j = 0;
// 	while (mapo[i])
// 	{
// 		j = 0;
// 		while (mapo[i][j])
// 		{
// 			if (mapo[i][j] == 'N' || mapo[i][j] == 'E' || mapo[i][j] == 'W' || mapo[i][j] == 'S')
// 			{
// 				player->angle = 0;
// 				if (mapo[i][j] == 'N')
// 					player->angle = M_PI_2;
// 				else if (mapo[i][j] == 'W')
// 					player->angle = M_PI;
// 				else if (mapo[i][j] == 'S')
// 					player->angle = M_PI_2 * 3;
// 				player->p.y = i * 10 + 2;
// 				player->p.x = j * 10 + 2;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void ft_start(t_map *g)
{
	t_window *win;
	// int j;
	win = (t_window *)ft_calloc(1, sizeof(t_window));
	win->screen = (t_cord *)ft_calloc(1, sizeof(t_cord));

	win->screen->x = 1280;
	win->screen->y = 720;
	printf("win.x=%d,y=%d\n", win->screen->x, win->screen->y);
	win->player = g->player;
	win->map = g;
	win->map->wide = g->wide;
	win->map->len = g->len;
	win->t.ea = mlx_load_png(g->ea);
	win->t.so = mlx_load_png(g->so);
	win->t.no = mlx_load_png(g->no);
	win->t.we = mlx_load_png(g->we);
	printf("win.x=%d\n", g->len);
	//check_zero_surrond(win.map.mapo);
	// win->map.lenght--;
	// win->map.wide = i;

	init_val(win);
	// free_all(win, strs);
}

// int main(int ac, char **av)
// {
// 	int		fd;
// 	char	**strs;
// 	int		i;

// 	i = 0;
// 	if (ac == 2)
// 	{
// 		strs = (char **)ft_calloc(100, sizeof(char *));
// 		fd = open(av[1], O_RDWR);
// 		while (1)
// 		{
// 			strs[i] = get_next_line(fd);
// 			if (!strs[i])
// 				break;
// 			i++;
// 		}
// 		//i = check_textures(strs, &t, &floor, &ceiling);
// 		ft_start(i, strs);
// 	}
// 	else
// 		return (1);
// }

