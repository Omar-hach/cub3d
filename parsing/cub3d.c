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

void error(void)
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
}
void	get_angle(char	c, t_player *player)
{
	if(c == 'E')
		player->angle = 0;
	else if(c == 'N')
		player->angle = PI / 2;
	else if(c == 'W')
		player->angle = PI;
	else if(c == 'S')
		player->angle = PI * 3 / 2;
}
void	get_player_location(t_window	*win, t_player *player, char **mapo)
{
	int i = 0;
	int j = 0;
	while(mapo[i])
	{
		j = 0;
		while(mapo[i][j])
		{
			if(mapo[i][j] == 'N' || mapo[i][j] == 'E' || mapo[i][j] == 'W' || mapo[i][j] == 'S')
			{
				get_angle(mapo[i][j], player);
				player->p.y = i * 50;
				player->p.x = j * 50;
			}
			j++;
		}
		i++;
	}

}
void ft_start(char *str, int i)
{
	t_player player;
	t_window win;
	int j;
	int fd = open(str, O_RDWR);
	char *dtr;
	int dtrsize = 0;
	win.map.wide = 0;
	win.map.width = 0;
	while (1)
	{
		dtr = get_next_line(fd);
		if (dtr == NULL)
			break;
		dtrsize++;
	}
	close(fd);
	fd = open(str, O_RDWR);

	win.map.mapc = (char **)ft_calloc(dtrsize + 1, sizeof(char *));
	win.map.mapc[win.map.wide] = get_next_line(fd);
	while (win.map.mapc[win.map.wide])
	{
		win.map.wide++;
		win.map.mapc[win.map.wide] = get_next_line(fd);
	}
	win.map.mapo = (char **)ft_calloc(dtrsize - i + 1, sizeof(char *));
	j = 0;
	while (win.map.mapc[i + 1][0] == '\n')
		i++;
	while (win.map.mapc[i + 1])
	{
		if (ft_strlen(win.map.mapc[i + 1]) > win.map.lenght)
			win.map.lenght = ft_strlen(win.map.mapc[i + 1]);
		win.map.mapo[j] = ft_strdup(win.map.mapc[i + 1]);
		j++;
		i++;
	}
	i = 0;
	while(win.map.mapo[i])
		i++;	
	get_player_location(&win,&player, win.map.mapo);

	 
	win.map.lenght--;
	win.map.wide = i;
	init_val(&win ,&player);
	free_all(&win, win.map.mapc);
}

int main(int ac, char **av)
{

	int fd;
	char **strs;
	int i;
	t_textures t;
	t_color floor;
	t_color ceiling;

	i = 0;
	if (ac == 2)
	{
		strs = (char **)ft_calloc(100 ,sizeof(char *));
		fd = open(av[1], O_RDWR);
		while (1)
		{
			strs[i] = get_next_line(fd);
			if (!strs[i])
				break;
			i++;
		}
		i = check_textures(strs, &t, &floor, &ceiling);
		ft_start(av[1], i);

	}
	else
		return (1);
}
