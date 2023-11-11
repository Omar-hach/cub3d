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

t_vector	rotation_vect(t_vector vect, double deg)
{
	t_vector	new_vect;

	new_vect.x = vect.y * sin(deg) + vect.x * cos(deg);
	new_vect.y = vect.y * cos(deg) - vect.x * sin(deg);
	if (new_vect.y < 0.00000000000001
		&& new_vect.y > -0.0000000000001)
		new_vect.y = 0;
	if (new_vect.x < 0.00000000000001
		&& new_vect.x > -0.0000000000001)
		new_vect.x = 0;
	return (new_vect);
}

int	check_inside(t_window *win, t_point player)
{
	int	i;
	int	j;
	int x;
	int y;

	i = (player.y - 2) / 10;
	j = (player.x - 2) / 10;
	x = (player.y - 2) / 10;
	y = (player.x - 2) / 10;
	//ft_printf("x=%d,y=%d,angle=[%d][%d]\n",win->map.lenght,win->map.wide,  i, j);
	if (win->map.mapo[i][j] == '0' || win->map.mapo[i][j] == 'W'
			|| win->map.mapo[i][j] == 'E' || win->map.mapo[i][j] == 'N'
			|| win->map.mapo[i][j] == 'S')
		return (1);
	return (0);
}

t_point	mov_player(t_point player, t_vector v, mlx_t *mlxp)
{
	t_point	next_pos;

	//printf("[%.4f][%.4f]\n", v.x, v.y);
	next_pos = player;
	if (mlx_is_key_down(mlxp, MLX_KEY_W))
		next_pos = assign_point(next_pos.x + v.x,
				next_pos.y + v.y);
	if (mlx_is_key_down(mlxp, MLX_KEY_S))
		next_pos = assign_point(next_pos.x - v.x,
				next_pos.y - v.y);
	if (mlx_is_key_down(mlxp, MLX_KEY_D))
		next_pos = assign_point(next_pos.x + v.y,
				next_pos.y - v.x);
	if (mlx_is_key_down(mlxp, MLX_KEY_A))
		next_pos = assign_point(next_pos.x - v.y,
				next_pos.y + v.x);
	//printf("next_pos==[%.4f][%.4f]\n", next_pos.x, next_pos.y);
	return (next_pos);
}

void	keyhook(void *param)
{
	t_window	*win;
	t_point		next_pos;
	t_ray		r;

	win = (t_window *)param;
	mlx_delete_image(win->mlx_ptr, win->img);
	win->img = mlx_new_image(win->mlx_ptr,
			win->screen.x, win->screen.y);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_RIGHT))
		win->player->angle = angle_adjast(win->player->angle, '+');
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_LEFT))
		win->player->angle = angle_adjast(win->player->angle, '-');
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(win->mlx_ptr, win->img);
		free_all(win, win->map.mapo);// there is  lot of leaks hire
		exit(0);
	}
	next_pos = assign_int_point(win->player->p.x, win->player->p.y);
	win->player->v.x = win->player->speed;
	win->player->v.y = 0;
	win->player->v = rotation_vect(win->player->v, angle_adjast(win->player->angle, '*'));
	//printf("v=%f=[%.4f][%.4f]\n", win->player->angle,win->player->v.x, win->player->v.y);
	next_pos = mov_player(win->player->p, win->player->v, win->mlx_ptr);
	r = draw_scene(win, win->map.mapo, next_pos);
	draw_mini_map(win, win->map.mapo);
	draw_line(win, win->player->p, r.p);
	//printf("%p=x=%.2f,y=%.2f, v.x=%.2f v.y=%.2f angle=%.2f\n",win->player, win->player->p.x, win->player->p.y,
	//	win->player->v.x, win->player->v.y, win->player->angle);
	//ft_draw_scene(win, &win->player.p, lv);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
}

void	init_val(t_window *win)
{
	t_ray	r;

	win->screen.x = 1280;
	win->screen.y = 720;
	win->player->speed = 0.5;
	win->player->v.x = win->player->speed;
	win->player->v.y = 0;
	win->player->v = rotation_vect(win->player->v, angle_adjast(win->player->angle, '*'));
//	win->t.ea = mlx_load_png("assets/m64 atlantic.png");
//	win->t.so = mlx_load_png("assets/m64 atlantic.png");
//	win->t.no = mlx_load_png("assets/m64 atlantic.png");
//	win->t.we = mlx_load_png("assets/m64 atlantic.png");

	win->t.ea = mlx_load_png("assets/m64 atlantic.png");
	win->t.so = mlx_load_png("assets/bowser_2.png");
	win->t.no = mlx_load_png("assets/bowser3.png");
	win->t.we = mlx_load_png("assets/egypt.png");
	win->mlx_ptr = mlx_init(win->screen.x, win->screen.y,
			"Super Duper Cool 3D Game!!!", false);
	if (!win->mlx_ptr)
		error();
	win->img = mlx_new_image(win->mlx_ptr,
			win->screen.x, win->screen.y);
	if (!win->img)
		error();
	//printf("p[%p].x=%.0f,p.y=%.0f\n",win->player, (win->player->p.x - 2) / 10, (win->player->p.y - 2) / 10);
	//printf("p[%p].x=%.0f,p.y=%.0f\n",win->t.ea, win->player->p.x, win->player->p.y);
	r = draw_scene(win, win->map.mapo, win->player->p);
	draw_mini_map(win, win->map.mapo);
	draw_line(win, win->player->p, r.p);
	mlx_loop_hook(win->mlx_ptr, &keyhook, win);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	mlx_loop(win->mlx_ptr);
}
	/*win->img = mlx_new_image(win->mlx_ptr,
			win->map.lenght * 10 + 4, win->map.wide * 10 + 4);
	if (!win->img)
		error();*/
