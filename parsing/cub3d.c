/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 02:12:43 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/17 02:12:46 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_exit(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

void	ft_start(t_map *g)
{
	t_window	*win;
	int			j;

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
	free(g->ea);
	free(g->so);
	free(g->no);
	free(g->we);
	free(g->c);
	free(g->f);
	j = -1;
	while (g->full_file[++j])
		free(g->full_file[j]);
	init_val(win);
	if (!win->t.ea || !win->t.so || !win->t.we || !win->t.no 
		|| !win->t.ceileng || !win->t.floor)
	{
		free_all(win, win->map->mapo);
		//printf("error=\n");
		exit(1);
	}
	printf("color floor = #%X ceileng = #%X\n",win->t.floor, win->t.ceileng);
	free_all(win, win->map->mapo);
}

void	parser(t_map *g, int fd)
{
	int	error;
	int	i;

	if (get_data(fd, g) > 0)
	{
		free(g->split_line);
		free(g);
		ft_exit("Error need more information, Exiting...\n");
	}
	printf("here\n");
	if (get_map(fd, g) < 3)
	{
		free(g->split_line);
		free(g->map_line);
		free(g);
		ft_exit("Error no map, Exiting...\n");
	}
	g->mapo = convert_map(g->map_line);
	g->full_file = convert_map(g->split_line);
	free(g->split_line);
	free(g->map_line);
	get_len_wide(g);
	error = 0;
	error += check_borders_line(g);
	error += check_borders_col(g);
	error += check_map_line(g->mapo);
	if(error)
	{
		free(g->mapo);
		free(g->full_file);
	}
	get_text(g); 
	g->player = ft_calloc(1, sizeof(t_player));
	g->player = get_player_location(g->player, g, &i);
	printf("no = >%s-\n", g->so);
	printf("no = >%s-\n", g->so);
	printf("no = >%s-\n", g->no);
	printf("no = >%s-\n", g->ea);
	printf("no = >%s-\n", g->we);
	printf("no = >%s-\n", g->c);
	printf("no = >%s-\n", g->f);
	printf("----------------\t\n");
	i = 0;
	while (g->mapo[i])
		printf("%s\n", g->mapo[i++]);
	ft_start(g);
}

void	check_name(int fd, char *file)
{
	int	i;

	if (fd < 1)
		ft_exit("Error No file wrong.\n");
	i = ft_strlen(file);
	if (i < 5)
		ft_exit("Error No file wrong.\n");
	if (file[i - 4] != '.' || file[i - 3] != 'c'
		|| file[i - 2] != 'u' || file[i - 1] != 'b')
		ft_exit("Error Found wrong line length, Exiting...\n");
}

void	check_lines(char* file)
{
	char	*line;
	int		fd;
	int		len;

	fd = open(file, O_RDONLY);
	check_name(fd, file);
	line = get_next_line(fd);
	len = 0;
	while (line != NULL)
	{
		/*if (ft_strlen(line) < 2 && line[0] != '\n'
			&& (line[0] == '1' || line[0] == ' '))
			ft_exit("Error wrong elements, Exiting...\n");*/
		if(line[0] != '\n')
			len++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (len < 6)
		ft_exit("Error need more information, Exiting...\n");
}

int	main(int ac, char **av)
{
	t_map	*g;
	int		fd;

	check_lines(av[1]);
	fd = open(av[1], O_RDONLY);
	if (ac == 2 && fd > -1)
	{
		g = ft_calloc(1, sizeof(t_map));
		parser(g, fd);
	}
	else
		ft_exit("Error need more information, Exiting...");
}
