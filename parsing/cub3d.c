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

void ft_start(char *str)
{
	t_window win;
	// int j;
	// nt i;
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

	win.map.elem = (char **)ft_calloc(dtrsize + 1, sizeof(char *));
	win.map.elem[win.map.wide] = get_next_line(fd);
	check_first_line(win.map.elem[win.map.wide]);
	while (win.map.elem[win.map.wide])
	{
		if (ft_strlen(win.map.elem[win.map.wide]) > win.map.lenght)
			win.map.lenght = ft_strlen(win.map.elem[win.map.wide]);
		// printf("%s", win.map.elem[win.map.wide]);
		win.map.wide++; // map win.map.width * 50 + 20
		win.map.elem[win.map.wide] = get_next_line(fd);
	}
	check_zero_surrond(win.map.elem);
	win.map.lenght--;
	init_val(&win);
	free_all(&win, win.map.elem);
}

int main(int ac, char **av)
{

	int fd;
	char **strs;
	int	i;
	t_textures t;
	i = 0;
	if (ac == 2)
	{

		strs = malloc(100 * sizeof(char *));
		fd = open(av[1], O_RDWR);
		while(1)
		{
			strs[i] = get_next_line(fd);
			if(!strs[i])
				break;
			i++;
		}
		check_textures(strs, &t);
		// ft_start(av[1]);
	}
	else
		return (1);
}

