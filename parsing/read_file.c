/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouzi < mdouzi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:39:59 by mdouzi            #+#    #+#             */
/*   Updated: 2023/11/15 11:50:52 by mdouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_empty(char c)
{
	if (c == '\0')
		return (1);
	else
		return (0);
}

int	not_map(char c)
{
	if (c == '0' || c == '1')
		return (1);
	else
		return (0);
}

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	free_all(t_window *win, char **elem)
{
	int	j;

	j = -1;
	while (elem[++j])
		free(elem[j]);
	free(elem);
	if (win->img)
		mlx_delete_image(win->mlx_ptr, win->img);
	if (win->mlx_ptr)
		mlx_terminate(win->mlx_ptr);
	free(win->player);
	free(win->screen);
	free(win);
	system("leaks $(ps | grep cub3D | awk '{if (NR==1) print$1}')");
}

void	get_last_n_line(char *line, char **kep)
{
	*kep = ft_strjoin(*kep, line);
	*kep = ft_strjoin(*kep, "\n");
}

int	get_data(int fd, t_map *g)
{
	int		i;
	char	*line;

	i = 6;
	g->split_line = ft_strdup(""); 
	line = get_next_line(fd);
	while (line != NULL && i > 0) 
	{
		if (ft_isalpha(line[0]))
		{
			get_last_n_line(line, &g->split_line);
			i--;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (i);
}

int	get_map(int fd, t_map *g)
{
	char	*line;
	int		l;

	l = 1;
	g->map_line = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		get_last_n_line(line, &g->map_line);
	free(line);
	line = get_next_line(fd);
	while (line != NULL) 
	{
		l++;
		if (line[0] != '\0' && line[1] != '\0')
			get_last_n_line(line, &g->map_line);
		if (line[0] == '\n')
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (l);
}

char	**convert_map(char *line)
{
	char	**str;

	str = ft_split(line, '\n');
	return (str);
}

int	play_char(char c, int *a)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		(*a)++;
		return (1);
	}
	else
		return (0);
}

void	get_len_wide(t_map *g)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	g->len = 0;
	g->wide = 0;
	while (g->mapo[j])
	{
		i = 0;
		while (g->mapo[j][i])
			i++;
		if (i > g->len)
			g->len = i;
		j++;
	}
	g->wide = j;
}
