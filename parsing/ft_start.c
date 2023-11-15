/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 05:12:43 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/12 05:12:48 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	free(win->screen);
	free(win);
	//system("leaks $(ps | grep cub3D | awk '{if (NR==1) print$1}')");
}

void get_player_location(t_player *player, char **mapo)
{
	int i = 0;
	int j = 0;
	while (mapo[i])
	{
		j = 0;
		while (mapo[i][j])
		{
			if (mapo[i][j] == 'N' || mapo[i][j] == 'E' || mapo[i][j] == 'W' || mapo[i][j] == 'S')
			{
				player->angle = 0;
				if (mapo[i][j] == 'N')
					player->angle = M_PI_2;
				else if (mapo[i][j] == 'W')
					player->angle = M_PI;
				else if (mapo[i][j] == 'S')
					player->angle = M_PI_2 * 3;
				player->p.y = i * 10 + 7;
				player->p.x = j * 10 + 2;
			}
			j++;
		}
		i++;
	}
}

void ft_start(int i, char **strs)
{
	t_window *win;
	int j;
	win = (t_window *)ft_calloc(1, sizeof(t_window));
	win->player = (t_player *)ft_calloc(1, sizeof(t_player));
	win->screen = (t_cord *)ft_calloc(1, sizeof(t_cord));
	win->map.mapo = (char **)ft_calloc(100 + 1, sizeof(char *));
	win->map.wide = 0;
	win->map.lenght = 0;

	j = 0;
	i = 7;
	while (strs[i][0] == '\n')
		i++;
	check_tab(strs);
	while (strs[i])
	{
		if (ft_strlen(strs[i]) > win->map.lenght)
			win->map.lenght = ft_strlen(strs[i]);
		win->map.mapo[j] = ft_strdup(strs[i]);
		j++;
		i++;
	}
	i = 0;
	while (win->map.mapo[i])
		i++;
	get_player_location(win->player, win->map.mapo);
	check_map(win->map.mapo);
	//check_zero_surrond(win.map.mapo);
	win->map.lenght--;
	win->map.wide = i;

	init_val(win);
	free_all(win, strs);
}