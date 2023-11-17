/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouzi < mdouzi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:41:44 by mdouzi            #+#    #+#             */
/*   Updated: 2023/11/15 04:14:10 by mdouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_size(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	check_borders_line(t_map *g)
{
	int	i;
	int	j;

	i = -1;
	while (g->mapo[++i] != NULL)
	{
		j = 0;
		while (g->mapo[i][j] != '\0')
			j++;
		if (g->mapo[i][j - 1] != '1')
		{
			printf("error \n");
			return (1);
		}
	}
	i = -1;
	while (g->mapo[++i] != NULL)
	{
		if (g->mapo[i][0] != '1' && g->mapo[i][0] != ' ')
		{
			printf(".error\n");
			return (1);
		}
	}
	return (0);
}

int	check_borders_col(t_map *g)
{
	int	j;

	j = 0;
	while (g->mapo[0][j] != '\0')
	{
		if (g->mapo[0][j] != '1' && g->mapo[0][j] != ' ')
		{
			printf("=error \n");
			return (1);
		}
		j++;
	}
	j = 0;
	while (g->mapo[ft_size(g->mapo) - 1][j] != '\0')
	{
		if ((g->mapo[ft_size(g->mapo) - 1][j] != '1') &&
			(g->mapo[ft_size(g->mapo) - 1][j] != ' '))
		{
			printf("|error \n");
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_surending(char **str, int i, int j, int *pp)
{
	if ((str[j][i] != '1' && str[j][i] != ' ' && str[j][i] != '\n'
		&& str[j][i] != '0') && play_char(str[j][i], pp) == 0)
	{
		printf("error[%d][%d]-\n", j, i);
		return (1);
	}
	if ((str[j][i] == '0' || str[j][i] == 'N' || str[j][i] == 'W' 
		|| str[j][i] == 'E' || str[j][i] == 'S')
		&& ((int)ft_strlen(str[j + 1]) < (i + 1)
		|| (int)ft_strlen(str[j - 1]) < (i + 1)))
	{
		printf("error[%d][%d]&\n", j, i);
		return (1);
	}
	if ((str[j][i] == '0' || str[j][i] == 'N' || str[j][i] == 'W' 
		|| str[j][i] == 'E' || str[j][i] == 'S')
		&& (str[j][i + 1] == ' ' || str[j][i - 1] == ' '
		|| str[j + 1][i] == ' ' || str[j - 1][i] == ' '))
	{
		printf("error[%d][%d]+\n", j, i);
		return (1);
	}
	return (0);
}

int	check_map_line(char **str)
{
	int	i;
	int	j;
	int	pp;

	j = 0;
	pp = 0;
	while (str[++j + 1])
	{
		i = -1;
		while (str[j][++i] != '\0')
		{
			if (check_surending(str, i, j, &pp))
				return (1);
		}
	}
	if (pp != 1)
	{
		printf("Error: not exactly one player\n");
		return (1);
	}
	return (0);
}
