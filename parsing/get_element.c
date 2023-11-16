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

void get_player_location(t_player *player, t_map *g)
{
	int i = 0;
	int j = 0;
	while (g->mapo[i])
	{
		j = 0;
		while (g->mapo[i][j])
		{
			if (g->mapo[i][j] == 'N' || g->mapo[i][j] == 'E' || g->mapo[i][j] == 'W' || g->mapo[i][j] == 'S')
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
			j++;
		}
		i++;
	}
}

int compare_txt(char *str, char *cmp,int j)
{
	int i = 0;
	while(str[i] == cmp[i])
	{
		i++;
		if(i == j)
			return(1);
	}
	return(0);
}

void cut_txt(char *str, t_map *g, int op)
{
    int i = 2;
    int start = 0;

    while (str[i] && str[i] == ' ')
        i++;
    start = i;
    while (str[i])
        i++;

	if(op == 1)
		g->so = ft_substr(str, start, i);
	else if(op == 2)
		g->we = ft_substr(str, start, i);
	else if(op == 3)
		g->ea = ft_substr(str, start, i);
	else if(op == 4)
		g->no = ft_substr(str, start, i);
    else if(op == 5)
        g->c = ft_substr(str, start, i);
    else if(op == 6)
        g->f = ft_substr(str, start, i);
}

int get_text(t_map *g)
{
	int i = 0;
	while(g->full_file[i] !=  NULL)
	{
		if(compare_txt(g->full_file[i], "NO", 2) && !g->no)
			cut_txt(g->full_file[i], g, 4);
		else if(compare_txt(g->full_file[i], "SO", 2) && !g->so)
			cut_txt(g->full_file[i], g, 1);
		else if(compare_txt(g->full_file[i], "WE", 2) && !g->we)
			cut_txt(g->full_file[i], g, 2);
		else if(compare_txt(g->full_file[i], "EA", 2) && !g->ea)
			cut_txt(g->full_file[i], g, 3);
        /*else if(compare_txt(g->full_file[i], "C", 1) && !g->c)
            cut_txt(g->full_file[i], g, 5);
        else if(compare_txt(g->full_file[i], "F", 1) && !g->f)
            cut_txt(g->full_file[i], g, 6);*/
		i++;
	}
	return(1);
}
