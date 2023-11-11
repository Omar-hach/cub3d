/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 06:27:26 by ohachami          #+#    #+#             */
/*   Updated: 2023/11/11 06:27:32 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_mini_map(t_window *win, char **matrix)
{
	t_cord	cord;
	t_point	start;
	t_point	end;

	cord.x = -1;
	cord.y = -1;
	start = assign_int_point(0, 0);
	end = assign_int_point(win->map.wide * 10 + 4, win->map.lenght * 10 + 4);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_int_point(10, 10);
	while (++cord.x < win->map.wide)
	{
		cord.y = -1;
		while (++cord.y < win->map.lenght)
		{
			start = assign_int_point(cord.y * 10 + 2, cord.x * 10 + 2);
			if (matrix[cord.x][cord.y] == '1')
				cub_drawer(win->img, start, end, 0x09005EFF);
			else if ((matrix[cord.x][cord.y] != ' '
				&& matrix[cord.x][cord.y] != '\n') || !matrix[cord.x][cord.y])
				cub_drawer(win->img, start, end, 0xB8A649FF);
		}
	}
	player_drawer(win, win->player->p, 0xFF322BFF);
}

t_ray	draw_scene_b(t_window *win, char **matrix, t_point next_pos)
{
	double		plane;
	t_cord		cord;
	t_ray		r;
	t_vector	nv;
	t_vector	add_v;

	draw_background(win, ft_color(255,0,00), ft_color(0,0,255));
	next_pos = pos_adjast(win, next_pos);
	cord.x = -1;
	cord.y = 0;
	win->player->p = assign_point(next_pos.x, next_pos.y);
	if (check_inside(win, next_pos))
	{
		plane = 0;
		while (++cord.x <= win->screen.x)
		{
			plane = (2 * (double)cord.x / 40 - 32) * M_PI / (double)180;
			add_v.x = 1 * win->player->speed;
			add_v.y = 0;
			nv = assign_vect(win->player->speed, 0, win->player->angle + plane);
			r = raycast(win, matrix, nv);
			r.distance = sqrt(pow(r.p.x - win->player->p.x, 2) + pow(r.p.y - win->player->p.y, 2)) * (dot_vect(win->player->v, nv) / (norme_vect(nv) * norme_vect(win->player->v)));
			if (r.distance < 2)
				return (r);
			cord.y = (win->screen.y - win->screen.y / r.distance * 10) / 2 - 1; // 10 is the size of the cub
			texturess(win, r, cord);
		}
	}
	r = raycast(win, win->map.mapo, win->player->v);
	return (r);
}

void	keyhook_b(void *param)
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
	win->player->v = assign_vect(win->player->speed, 0, win->player->angle);
	next_pos = mov_player(win->player->p, win->player->v, win->mlx_ptr);
	r = draw_scene(win, win->map.mapo, next_pos);
	draw_mini_map(win, win->map.mapo);
	draw_line(win, win->player->p, r.p);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
}

void	init_val_b(t_window *win)
{
	t_ray	r;

	win->screen.x = 1280;
	win->screen.y = 720;
	win->player->speed = 0.5;
	win->player->v.x = win->player->speed;
	win->player->v.y = 0;
	win->player->v = rotation_vect(win->player->v, angle_adjast(win->player->angle, '*'));
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
	r = draw_scene(win, win->map.mapo, win->player->p);
	draw_mini_map(win, win->map.mapo);
	draw_line(win, win->player->p, r.p);
	mlx_loop_hook(win->mlx_ptr, &keyhook_b, win);
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
	mlx_loop(win->mlx_ptr);
}

void ft_start_b(int i, char **strs)
{
	t_window *win;
	int j;
	win = (t_window *)ft_calloc(1, sizeof(t_window));
	win->player = (t_player *)ft_calloc(1, sizeof(t_player));
	win->map.mapo = (char **)ft_calloc(100000 + 1, sizeof(char *));
	win->map.wide = 0;
	win->map.lenght = 0;

	j = 0;
	i = 7;
	while (strs[i][0] == '\n')
		i++;
	check_tab(strs);
	while (strs[i])
	{
		if (ft_strlen(strs[i]) > win->map.lenght)
			win->map.lenght = ft_strlen(strs[i]);
		win->map.mapo[j] = ft_strdup(strs[i]);
		j++;
		i++;
	}
	i = 0;
	while (win->map.mapo[i])
		i++;
	get_player_location(win->player, win->map.mapo);
	check_map(win->map.mapo);
	//check_zero_surrond(win.map.mapo);
	win->map.lenght--;
	win->map.wide = i;

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
