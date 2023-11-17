/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouzi < mdouzi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:51:50 by mdouzi            #+#    #+#             */
/*   Updated: 2023/11/15 06:31:32 by mdouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_player	*get_player_location(t_player *player, t_map *g, int *a)
{
	int	i;
	int	j;

	i = -1;
	while (g->mapo[++i])
	{
		j = -1;
		while (g->mapo[i][++j])
		{
			if (play_char(g->mapo[i][j], a))
			{
				player->angle = 0;
				if (g->mapo[i][j] == 'N')
					player->angle = M_PI_2;
				else if (g->mapo[i][j] == 'W')
					player->angle = M_PI;
				else if (g->mapo[i][j] == 'S')
					player->angle = M_PI_2 * 3;
				player->p.y = i * 10 + 7;
				player->p.x = j * 10 + 7;
			}
		}
	}
	return (player);
}

int	compare_txt(char *str, char *cmp, int j)
{
	int	i;

	i = 0;
	while (str[i] == cmp[i])
	{
		i++;
		if (i == j)
			return (1);
	}
	return (0);
}

void	cut_txt(char *str, t_map *g, int op)
{
	int	i;
	int	start;

	start = 0;
	i = 2;
	while (str[i] && str[i] == ' ')
		i++;
	start = i;
	while (str[i])
		i++;
	if (op == 1)
		g->so = ft_substr(str, start, i);
	else if (op == 2)
		g->we = ft_substr(str, start, i);
	else if (op == 3)
		g->ea = ft_substr(str, start, i);
	else if (op == 4)
		g->no = ft_substr(str, start, i);
	else if (op == 5)
		g->c = ft_substr(str, start, i);
	else if (op == 6)
		g->f = ft_substr(str, start, i);
}

int	get_text(t_map *g)
{
	int	i;

	i = 0;
	while (g->full_file[i] != NULL)
	{
		if (compare_txt(g->full_file[i], "NO ", 3) && !g->no)
			cut_txt(g->full_file[i], g, 4);
		else if (compare_txt(g->full_file[i], "SO ", 3) && !g->so)
			cut_txt(g->full_file[i], g, 1);
		else if (compare_txt(g->full_file[i], "WE ", 3) && !g->we)
			cut_txt(g->full_file[i], g, 2);
		else if (compare_txt(g->full_file[i], "EA ", 3) && !g->ea)
			cut_txt(g->full_file[i], g, 3);
		else if (compare_txt(g->full_file[i], "C ", 2) && !g->c)
			cut_txt(g->full_file[i], g, 5);
		else if (compare_txt(g->full_file[i], "F ", 2) && !g->f)
			cut_txt(g->full_file[i], g, 6);
		i++;
	}
	if (!g->we || !g->so || !g->no || !g->ea)
		return (printf("Error texture not found, Exiting...\n"));
	if (!g->f || !g->c)
		return (printf("Error color not found, Exiting...\n"));
	return (0);
}

int	prime_clore(char *color, char *num, int *i)
{
	int	j;
	int	prime;

	j = -1;
	while (color[*i] == ' ')
		(*i)++;
	if (!ft_isdigit(color[*i]))
		return (-2);
	while (color[*i] == '0')
		(*i)++;
	while (ft_isdigit(color[*i]) && ++j > -2)
		num[j] = color[(*i)++];
	if (color[*i] == ',' || !color[*i])
		(*i)++;
	else
		return (-3);
	prime = ft_atoi(num);
	if (ft_strlen(num) > 3 || prime < 0 || prime > 256)
		return (-1);
	ft_bzero(num, ft_strlen(num));
	return (prime);
}

int	get_color(char *color, int r, int g, int b)
{
	int		i;
	char	*num;

	i = -1;
	if (!color)
		return (0);
	while (color[++i])
	{
		if (color[i] == ',')
			r++;
	}
	if (r == 2)
	{
		i = 0;
		num = (char *)ft_calloc(1, sizeof(char));
		r = prime_clore(color, num, &i);
		g = prime_clore(color, num, &i);
		b = prime_clore(color, num, &i);
		free(num);
		if (r > -1 && g > -1 && b > -1)
			return (((r << 24) | (g << 16) | (b << 8) | 0xff));
	}
	printf("Error : check the rgb please\n");
	return (0);
}

//printf("color %d, %d, %d\n", r,g,b);
