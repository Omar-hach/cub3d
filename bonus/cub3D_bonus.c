/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:34:37 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/13 10:34:39 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*void mouse_b(double xpos, double ypos, void* param)
{
	t_window *win;
	int x;
	int	y;

	win = (t_window *)param;
	if(xpos > 0 && xpos < win->screen->x && ypos > 0 && ypos < win->screen->y)
	{
		printf("pos[%f][%f]\n", xpos, ypos);
	}
}*/

void	init_val_b(t_window *win)
{
	win->screen->x = 1280;
	win->screen->y = 720;
	win->player->speed = 0.5;
	win->player->v.x = win->player->speed;
	win->player->v.y = 0;
	win->player->v = assign_vect(win->player->speed, 0, win->player->angle);
	win->t.ea = mlx_load_png("assets/m64 atlantic.png");
	win->t.so = mlx_load_png("assets/bowser_2.png");
	win->t.no = mlx_load_png("assets/bowser3.png");
	win->t.we = mlx_load_png("assets/egypt.png");
	win->mlx_ptr = mlx_init(win->screen->x, win->screen->y,
			"Super Duper Cool 3D Game!!!", false);
	if (!win->mlx_ptr)
		error();
	win->img = mlx_new_image(win->mlx_ptr,
			win->screen->x, win->screen->y);
	if (!win->img)
		error();
	//mlx_cursor_hook(win->mlx_ptr, &mouse_b, win);
	mlx_loop_hook(win->mlx_ptr, &keyhook_b, win);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	mlx_loop(win->mlx_ptr);
}

void	ft_start_b(int i, char **strs)
{
	t_window	*win;
	int			j;

	win = (t_window *)ft_calloc(1, sizeof(t_window));
	win->player = (t_player *)ft_calloc(1, sizeof(t_player));
	win->screen = (t_cord *)ft_calloc(1, sizeof(t_cord));
	win->map->mapo = (char **)ft_calloc(100000 + 1, sizeof(char *));
	win->map->wide = 0;
	win->map->len = 0;
	j = 0;
	i = 7;
	while (strs[i][0] == '\n')
		i++;
	check_tab(strs);
	while (strs[i])
	{
		if (ft_strlen(strs[i]) > win->map->len)
			win->map->len = ft_strlen(strs[i]);
		win->map->mapo[j] = ft_strdup(strs[i]);
		j++;
		i++;
	}
	i = 0;
	while (win->map->mapo[i])
		i++;
	get_player_location(win->player, win->map->mapo);
	check_map(win->map->mapo);
	//check_zero_surrond(win.map.mapo);
	win->map->lenght--;
	win->map->wide = i;
	init_val_b(win);
	free_all(win, strs);
}

int main(int ac, char **av)
{
	int		fd;
	char	**strs;
	int		i;

	i = 0;
	if (ac == 2)
	{
		strs = (char **)ft_calloc(100, sizeof(char *));
		fd = open(av[1], O_RDWR);
		while (1)
		{
			strs[i] = get_next_line(fd);
			if (!strs[i])
				break;
			i++;
		}
		//i = check_textures(strs, &t, &floor, &ceiling);
		ft_start_b(i, strs);
	}
	else
		return (1);
}
