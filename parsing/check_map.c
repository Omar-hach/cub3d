/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:31:08 by sbellafr          #+#    #+#             */
/*   Updated: 2023/09/16 11:51:54 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_first_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '1' || str[i] == '\n' || str[i] == ' ') && str[i])
		{
			printf("Error\n");
			exit(0);
		}
		i++;
	}
	return (1);
}

int zero_or_one(char c)
{
	if (c != '0' && c != '1'  && c != 'N'  && c != 'S' && c != 'E' && c != 'W')
		return 1;
	return 0;
}
void check_tab(char **strs)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] && strs[i][j] == '\t')
			{
				printf("Error\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}
int	out_of_elements(char c)
{
	if(c != '1' && c != '0' && c != 'W' && c != ' ' &&  c != '\n'  && c != 'N'  && c != 'S' && c != 'E')
		return (1);
	return (0);
}
void	check_elements(char **strs)
{
	int i;
	int j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (out_of_elements(strs[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if(count > 0)
	{
		printf("er ror\n");
		exit(0);
	}
}
void check_zero_surrond(char **strs)
{
	int i;
	int j;

	j = 0;
	i = 0;

	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] && strs[i][j] == '0')
			{
				if (zero_or_one(strs[i][j + 1]) || zero_or_one(strs[i][j - 1]) || zero_or_one(strs[i + 1][j]) || zero_or_one(strs[i - 1][j]))
				{
					printf("Error\n");
					exit(0);
				}
			}
			j++;
		}
		i++;
	}
	check_tab(strs);
	check_elements(strs);
}

