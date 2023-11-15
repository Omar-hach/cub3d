/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:06:21 by sbellafr          #+#    #+#             */
/*   Updated: 2023/09/27 15:22:56 by sbellafr         ###   ########.fr       */
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
			while(str[i])
			{
				if(str[i] != ' ' && str[i] != '\n')
				{
					printf("Error : check the rgb please\n");
					exit(2);
				}
				i++;
			}
			buffer[j] = '\0';
			color->b = ft_atoi(buffer);
		}
		i++;
	}
	i = 0;
	j = 0;
	while(str[i])
	{
		if(str[i] == ',')
			j++;
		i++;
	}
	if(j > 2)
	{
		printf("Error : check the rgb \n");
		exit(2);
	}
}

void	check_textures_rgb(t_textures *t)
{
	int	i;

	i = 0;
	// i++;
	while (t->c[i])
	{
		if (!ft_isdigit(t->c[i]) && t->c[i] != 'C' && t->c[i] != ' ' && t->c[i] != ','  && t->c[i] != '\n')
		{
			printf("error there is an external component\n");
			exit(2);
		}
		i++;
	}
	i = 0;
	while (t->f[i])
	{
		if (!ft_isdigit(t->f[i]) && t->f[i] != 'F' && t->f[i] != ' ' && t->f[i] != ','  && t->f[i] != '\n')
		{
			printf("error there is an external component\n");
			exit(2);
		}
		i++;
	}
}

int check_textures(char **strs, t_textures *t, t_color *floor, t_color *ceiling)
{
	int i;
	int j;
	int last_line = 0;
	int count;

	count = 0;
	i = 0;
	j = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == 'N' && strs[i][j + 1] == 'O')
			{
				count++;
				if (i > last_line)
					last_line = i;
				t->no = ft_strdup(strs[i]);
			}
			else if (strs[i][j] == 'S' && strs[i][j + 1] == 'O')
			{
				count++;
				if (i > last_line)
					last_line = i;
				t->so = ft_strdup(strs[i]);
			}
			else if (strs[i][j] == 'E' && strs[i][j + 1] == 'A')
			{
				count++;
				if (i > last_line)
					last_line = i;
				t->ea = ft_strdup(strs[i]);
			}
			else if (strs[i][j] == 'W' && strs[i][j + 1] == 'E')
			{
				count++;
				if (i > last_line)
					last_line = i;
				t->we = ft_strdup(strs[i]);
			}
			else if (strs[i][j] == 'F')
			{
				count++;
				if (i > last_line)
					last_line = i;
				t->f = ft_strdup(strs[i]);
				ft_rgb(t->f, floor);
			}
			else if (strs[i][j] == 'C')
			{
				count++;
				if (i > last_line)
					last_line = i;
				t->c = ft_strdup(strs[i]);
				ft_rgb(t->c, ceiling);
			}
			j++;
		}
		i++;
	}
	if(count != 6)
	{
		printf("error check the textures or thr rgb\n");
		exit(2);
	}
	check_textures_rgb(t);
	return (last_line);
}
