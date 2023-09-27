/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:03:30 by ohachami          #+#    #+#             */
/*   Updated: 2023/09/14 19:03:34 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point	assign_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

int	check_inside(t_window *win, t_point *player)
{
	int	i;
	int	j;

	i = (player->y + 15) / 50;
	j = (player->x + 15) / 50;
	//ft_printf("x=%d,y=%d,angle=[%d][%d]\n",win->map.lenght,win->map.wide,  i, j);
	if (win->map.elem[i][j] == '1')
			return (0);
	return (1);
}

t_point	mov_player(t_player player, int x, int y)
{
	player.p.y += y * cos(player.angle) - x * sin(player.angle);
	player.p.x += y * sin(player.angle) + x * cos(player.angle);
	printf("x=%.2f,y=%.2f,cos=%f, sin=%f angle=%.2f\n",player.p.x, player.p.y,
			cos(player.angle), sin(player.angle), player.angle);
	return (player.p);
}

void	keyhook(void *param)
{
	t_window	*win;
	t_point		start;


	win = (t_window *)param;
	mlx_delete_image(win->mlx_ptr, win->img);
	start = win->player.p;
	win->img = mlx_new_image(win->mlx_ptr, win->map.lenght * 50 + 20, win->map.wide * 50 + 20);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_W))
		start = mov_player(win->player, 1, 0);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_S))
		start = mov_player(win->player, -1, 0);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_D))
		start = mov_player(win->player, 0, 1);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_A))
		start = mov_player(win->player, 0, -1);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_RIGHT))
		win->player.angle = angle_adjast(win->player.angle, '+');
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_LEFT))
		win->player.angle = angle_adjast(win->player.angle, '-');
	ft_draw_map(win, win->map.elem, &start);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	// mlx_image_to_window(win->mlx_ptr, win->img2, 0, 0);
	//win->img2 = mlx_put_string(win->mlx_ptr, "lol", 00, 00);
}

void	init_val(t_window	*win)
{
	win->mlx_ptr = mlx_init(win->map.lenght * 50 + 20, win->map.wide * 50 + 20, "Test", true);
	if (!win->mlx_ptr)
		error();
	win->img = mlx_new_image(win->mlx_ptr, win->map.lenght * 50 + 20, win->map.wide * 50 + 20);
	if (!win->img)
		error();
	win->player.p = assign_point(360, 110); // first find the player and it is cordination.
	win->player.angle = 0;
	ft_draw_map(win, win->map.elem, &win->player.p);
	//printf("|x=%d,y=%d",win.player.p.x, win.player.p.y);
	mlx_loop_hook(win->mlx_ptr, &keyhook, win);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	mlx_loop(win->mlx_ptr);
}
