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
#define WIDTH 400
#define HEIGHT 500

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
}

void	ft_start(char *str)
{
	t_window win;
	//nt i;
	int fd = open(str, O_RDWR);


	win.map.wide = 0;
	win.map.lenght = 0;
	win.map.elem = (char **)ft_calloc(100, sizeof(char *));
	win.map.elem[0] = get_next_line(fd);
	while (win.map.elem[win.map.wide])
	{
		if(ft_strlen(win.map.elem[win.map.wide]) > win.map.lenght)
			win.map.lenght = ft_strlen(win.map.elem[win.map.wide]);
		printf("%s", win.map.elem[win.map.wide]);
		win.map.wide++;
		win.map.elem[win.map.wide] = get_next_line(fd);
	}
	win.map.lenght--;
	init_val(&win);
	free_all(&win, win.map.elem);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		ft_start(av[1]);
	else
		return (1);
}

