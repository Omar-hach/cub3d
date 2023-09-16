/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:06:21 by sbellafr          #+#    #+#             */
/*   Updated: 2023/09/16 18:44:15 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void check_textures(char **strs, t_textures *t)
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
			if (strs[i][j] == 'N' && strs[i][j + 1] == 'O')
				t->no = ft_strdup(strs[i]);
			else if (strs[i][j] == 'S' && strs[i][j + 1] == 'O')
				t->so = ft_strdup(strs[i]);
			else if (strs[i][j] == 'E' && strs[i][j + 1] == 'A')
				t->ea = ft_strdup(strs[i]);
			else if (strs[i][j] == 'W' && strs[i][j + 1] == 'E')
				t->we = ft_strdup(strs[i]);
			else if (strs[i][j] == 'F')
				t->f = ft_strdup(strs[i]);
			else if (strs[i][j] == 'C')
				t->c = ft_strdup(strs[i]);
			j++;
		}
		i++;
	}
}
