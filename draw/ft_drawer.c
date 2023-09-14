/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:03:30 by ohachami          #+#    #+#             */
/*   Updated: 2023/09/14 22:33:42 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


t_point assign_point(int x, int y, int color)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.color = color;
	return (p);
}

int check_inside(t_window *win, t_point *player)
{
	int i;
	int j;

	i = (player->y + 10) / 50;
	j = (player->x + 10) / 50;
	//ft_printf("angle=[%d][%d]\n", i, j);
	if(!i || !j)
	{
		player->y += !i;
		player->x += !j;
		return(0);
	}
	if(win->map.elem[i][j] == '1')
	{
		if(win->map.elem[i + 1][j] == '1' || win->map.elem[i - 1][j] == '1')
			player->y--;
		if(win->map.elem[i][j + 1] == '1' || win->map.elem[i][j - 1] == '1')
			player->x--;
		return(0);
	}
	else
	{
		return(1);
	}
}


t_player	mov_player(t_player player, int x, int y, float angle)
{
	player.p.x += x;
	player.p.y += y;
	player.angle = angle;
	return(player);
}

void	keyhook(void *param)
{
	t_window	*win = (t_window *)param;
	//t_point		start;
	//t_point		end;
	//int			i;

	mlx_delete_image(win->mlx_ptr, win->img);
	//mlx_delete_image(win->mlx_ptr, win->img2);
	//printf("angle=%f",win->player.angle);
	win->img = mlx_new_image(win->mlx_ptr, win->map.lenght * 50 + 20, win->map.wide * 50 + 20);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_S) && check_inside(win, &win->player.p))
	{
		win->player.p.x += cos(win->player.angle * M_PI / 180);
		win->player.p.y -= sin(win->player.angle * M_PI / 180);
		//ft_printf("x=%d,y=%d",win->player.p.x, win->player.p.y);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_W) && check_inside(win, &win->player.p))
	{
		win->player.p.x -= cos(win->player.angle * M_PI / 180);
		win->player.p.y += sin(win->player.angle * M_PI / 180);
		//ft_printf("x=%d,y=%d",win->player.p.x, win->player.p.y);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_D) && check_inside(win, &win->player.p))
	{
		win->player.p.x -= sin(win->player.angle * M_PI / 180);
		win->player.p.y -= cos(win->player.angle * M_PI / 180);
		//ft_printf("x=%d,y=%d",win->player.p.x, win->player.p.y);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_A) && check_inside(win, &win->player.p))
	{
		win->player.p.x += sin(win->player.angle * M_PI / 180);
		win->player.p.y += cos(win->player.angle * M_PI / 180);
		//ft_printf("x=%d,y=%d",win->player.p.x, win->player.p.y);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_RIGHT))
	{
		win->player.angle = angle_adjast(win->player.angle, '+');
		
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_LEFT))
	{
		win->player.angle = angle_adjast(win->player.angle, '-');
	}
	ft_draw_map(win, win->map.elem, &win->player);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	// mlx_image_to_window(win->mlx_ptr, win->img2, 0, 0);
	//win->img2 = mlx_put_string(win->mlx_ptr, "lol", 00, 00);
}

void init_val(t_window	*win)
{
	win->mlx_ptr = mlx_init(win->map.lenght * 50 + 20, win->map.wide * 50 + 20, "Test", true);
	if (!win->mlx_ptr)
		error();
	win->img = mlx_new_image(win->mlx_ptr, win->map.lenght * 50 + 20, win->map.wide * 50 + 20);
	if (!win->img)
		error();
	win->player.p = assign_point(310, 60, 0); // first find the player and it is cordination.
	win->player.angle = 0;
	ft_draw_map(win, win->map.elem, &win->player);
	//printf("|x=%d,y=%d",win.player.p.x, win.player.p.y);
	mlx_loop_hook(win->mlx_ptr, &keyhook, win);
	ft_printf(" |OK| \n");
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	mlx_loop(win->mlx_ptr);
}
