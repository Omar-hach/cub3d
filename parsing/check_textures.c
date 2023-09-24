/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:06:21 by sbellafr          #+#    #+#             */
/*   Updated: 2023/09/24 13:23:45 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_rgb(char *str, t_color *color)
{
	int i = 0;
	int j = 0;
	char *buffer = malloc(3);
	while (str[i])
	{
		if (ft_isalpha(str[i]))
		{
			i++;
			while (!ft_isalnum(str[i]))
				i++;
			while (str[i] && ft_isalnum(str[i]))
			{
				buffer[j] = str[i];
				i++;
				j++;
			}
			buffer[j] = '\0';
			color->r = ft_atoi(buffer);
			while (!ft_isalnum(str[i]))
				i++;
			j = 0;
			while (str[i] && ft_isalnum(str[i]))
			{
				buffer[j] = str[i];
				i++;
				j++;
			}
			buffer[j] = '\0';
			color->g = ft_atoi(buffer);
			while (!ft_isalnum(str[i]))
				i++;
			j = 0;
			while (str[i] && ft_isalnum(str[i]))
			{
				buffer[j] = str[i];
				i++;
				j++;
			}
			buffer[j] = '\0';
			color->b = ft_atoi(buffer);
		}
		i++;
	}
}
int check_textures(char **strs, t_textures *t, t_color *floor, t_color *ceiling)
{
	int i;
	int j;
	int last_line = 0;
	i = 0;
	j = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == 'N' && strs[i][j + 1] == 'O')
			{
				if (i > last_line)
					last_line = i;
				t->no = ft_strdup(strs[i]);
			}
			else if (strs[i][j] == 'S' && strs[i][j + 1] == 'O')
			{
				if (i > last_line)
					last_line = i;
				t->so = ft_strdup(strs[i]);
			}
			else if (strs[i][j] == 'E' && strs[i][j + 1] == 'A')
			{
				if (i > last_line)
					last_line = i;
				t->ea = ft_strdup(strs[i]);
			}
			else if (strs[i][j] == 'W' && strs[i][j + 1] == 'E')
			{
				if (i > last_line)
					last_line = i;
				t->we = ft_strdup(strs[i]);
			}
			else if (strs[i][j] == 'F')
			{
				if (i > last_line)
					last_line = i;
				t->f = ft_strdup(strs[i]);
				ft_rgb(t->f, floor);
			}
			else if (strs[i][j] == 'C')
			{
				if (i > last_line)
					last_line = i;
				t->c = ft_strdup(strs[i]);
				ft_rgb(t->c, ceiling);
			}
			j++;
		}
		i++;
	}
	i = 0;
	return (last_line);
}
