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

int is_empty(char c)
{
	if(c == '\0')
		return(1);
	else
		return(0);
}
int not_map(char c)
{
	if(c == '0' || c == '1')
		return(1);
	else
		return(0);
}

void get_last_n_line(char *line, char **kep) {
    *kep = ft_strjoin(*kep, line);
    *kep = ft_strjoin(*kep, "\n");
}

int get_data(int fd, t_map *g) {
    int i = 6;
    char *line;

    g->split_line = ft_strdup(""); 
    line = NULL;
    while ((line = get_next_line(fd)) != NULL && i > 0) {
        if (line[0] == '\0' || line[0] == '\n')
        {
            free(line);
            line = get_next_line(fd);
        }
         if(ft_isalpha(line[0]) ) {
            get_last_n_line(line, &g->split_line);
            free(line);
            line = NULL;
            i--;
        }
        else
            free(line);
    }
    while (is_empty(line[0]) && line[1] == '\0') {
        free(line);
        line = get_next_line(fd);
    }
	g->map_line = ft_strdup(""); 
    get_last_n_line(line, &g->map_line);
    free(line);
    return 1;
}

int get_map(int fd, t_map *g) 
{
    char *line;
    while ((line = get_next_line(fd)) != NULL && line[0] == '\0')
    {
        free(line);
        line = NULL;
    }
    get_last_n_line(line, &g->map_line);
    while ((line = get_next_line(fd)) != NULL) 
    {
        if (line[0] == '\0' || line[1] == '\0') {
            free(line);
        }
        else
        {
            get_last_n_line(line, &g->map_line);
            free(line);
            line = NULL;
        }
    }
    return 1;
}


char ** convert_map(char *line)
{
	char **str;
	str = ft_split(line, '\n');
	return(str);
}


int play_char(char c, int *a)
{
    if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
    {
        (*a)++;
        return 1;
    }
    else
        return 0;
}


void get_len_wide(t_map *g)
{
    int j = 0;
    int i = 0;

    g->len = 0;
    g->wide = 0;

    while (g->mapo[j])
    {
        i = 0;
        while (g->mapo[j][i])
            i++;
        if (i > g->wide)
            g->len = i;
        j++;
    }
    g->wide = j;
}
void parser(t_map *g, int fd)
{
    g->player = ft_calloc(1, sizeof(t_player));
    get_data(fd, g);
    get_map(fd, g);
    g->mapo = convert_map(g->map_line);
    g->full_file = convert_map(g->split_line);
    check_borders_line(g);
    check_borders_col(g);
    get_player_location(g->player, g);
    get_text(g);
    check_map_line(g->mapo);
    get_len_wide(g);

    int i = 0;
    printf("no = >%s-\n", g->so);
    printf("no = >%s-\n", g->no);
    printf("no = >%s-\n", g->ea);
    printf("no = >%s-\n", g->we);

    printf("no = >%s-\n", g->c);
    printf("no = >%s-\n", g->f);
    
    printf("----------------\t\n");
    while(g->mapo[i])
        printf("%s\n", g->mapo[i++]);
    ft_start(g);
}



int main(int ac, char **av)
{
    t_map *g;
    int fd;   
    if(ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        g = ft_calloc(1, sizeof(t_map));
        parser(g, fd);
    }
    else
    {
        ft_putstr_fd("no map", 2);
        return(1);
    }
}