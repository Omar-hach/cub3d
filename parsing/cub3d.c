/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:58:11 by sbellafr          #+#    #+#             */
/*   Updated: 2023/09/03 00:44:01 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define WIDTH 400
#define HEIGHT 500

t_point assign_point(int x, int y, int color)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.color = color;
	return (p);
}

void	draw_line(t_window *win, t_point start, t_point end)
{
	t_point	line;
	float	big;
	t_point	steps;
	t_point	pixels;
	int		i;

	i = 0;
	line.x = end.x - start.x;
	line.y = end.y - start.y;
	if (abs(line.x) > abs(line.y))
		big = abs(line.x);
	else
		big = abs(line.y);
	steps.x = line.x / big;
	steps.y = line.y / big;
	pixels = start;
	while (i < big)
	{
		printf("y=%d x=%d\n", (int)pixels.y / 50, (int)pixels.x / 50);
		printf("y=%d x=%d\n", (int)start.y, (int)start.x);
		if (win->map.elem[(int)pixels.x / 50][(int)pixels.y / 50] == '1') // the problem is here pixels.y overflow
			break ;
		mlx_put_pixel(win->img, (int)pixels.x, (int)pixels.y, 0x1100FFff);
		pixels.x += steps.x;
		pixels.y += steps.y;
		i++;
	}
}

void	cub_drawer(mlx_image_t *img, t_point start, t_point end, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < end.x - 1)
	{
		j = 0;
		while (j < end.y - 1)
		{
			mlx_put_pixel(img, start.x + i, start.y + j, color);
			j++;
		}
		i++;
	}
}

t_point	player_drawer(mlx_image_t *img, t_point pos, int color)
{
	int	r;
	float deg;

	r = 0;
	deg = 0;
	while(r < 11)
	{
		deg = 0;
		while (deg < M_PI * 2)
		{
			mlx_put_pixel(img, pos.x + r * cos(deg),
				pos.y + r * sin(deg), color);
			deg +=  M_PI / 180;
		}
		r++;
	}
	return(pos);
}

t_point	ft_draw_map(t_window *win, char **matrix, t_point player)
{
	int		i;
	int		j;
	t_point	start;
	t_point	end;

	i = -1;
	j = -1;
	start = assign_point(0, 0, 0);
	end = assign_point(win->map.wide * 50 + 20, HEIGHT, 0);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_point(50, 50, 0);
	while (++i < win->map.wide)
	{
		j = -1;
		while (++j < 9)
		{
			start = assign_point(i * 50 + 10, j * 50 + 10, 0);
			if (matrix[i][j] == '1')
				cub_drawer(win->img, start, end, 0x09005EFF);
			else
				cub_drawer(win->img, start, end, 0xB8A649FF);
			if(matrix[i][j] == 'P')
				player = player_drawer(win->img, start, 0xFF322BFF);
		}
	}
	return(player);
}

void	keyhook(void *param)
{
	t_window	*win = (t_window *)param;
	t_point		start;
	//t_point		end;
	int			i;

	mlx_delete_image(win->mlx_ptr, win->img);
	win->img = mlx_new_image(win->mlx_ptr, win->map.wide * 50 + 20, HEIGHT);
	printf("x=%d,y=%d",win->player.p.x, win->player.p.y);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_S))
	{
		win->player.p.x -= cos(win->player.angle * RAD);
		win->player.p.y -= sin(win->player.angle * RAD);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_W))
	{
		win->player.p.x += cos(win->player.angle * RAD);
		win->player.p.y += sin(win->player.angle * RAD);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_D))
	{
		win->player.p.x -= sin(win->player.angle * RAD);
		win->player.p.y += cos(win->player.angle * RAD);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_A))
	{
		win->player.p.x += sin(win->player.angle * RAD);
		win->player.p.y -= cos(win->player.angle * RAD);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_RIGHT))
		win->player.angle++;
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_LEFT))
		win->player.angle--;
	win->player.p = ft_draw_map(win, win->map.elem, win->player.p);
	//player_drawer(win->img, win->player.p, 0xFF322BFF);
	start.x = win->player.p.x;
	start.y = win->player.p.y;
	i = -30;
	/*while (i < 30)
	{
		end.x = win->player.p.x + cos((win->player.angle + i) * RAD) * 1000;
		end.y = win->player.p.y + sin((win->player.angle + i) * RAD) * 1000;
		//draw_line(win, start, end);
		i++;
	}*/
	mlx_image_to_window(win->mlx_ptr, win->img, 0, 0);
}

// static void ft_error(void)
// 
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

static void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	ft_start(char *str)
{
	t_window win;
	//nt i;
	int j;
	int fd = open(str, O_RDWR);


	win.map.wide = 0;
	win.map.elem = (char **)ft_calloc(100, sizeof(char *));
	win.map.elem[win.map.wide] = get_next_line(fd);
	while (win.map.elem[win.map.wide])
	{
		printf("%s", win.map.elem[win.map.wide]);
		win.map.wide++;
		win.map.elem[win.map.wide] = get_next_line(fd);
	}
	win.mlx_ptr = mlx_init(win.map.wide * 50 + 20, HEIGHT, "Test", true);
	if (!win.mlx_ptr)
		error();
	win.img = mlx_new_image(win.mlx_ptr, win.map.wide * 50 + 20, HEIGHT);
	if (!win.img)
		error();
	win.player.p = ft_draw_map(&win, win.map.elem, win.player.p);
	//printf("x=%d,y=%d",win.player.p.x, win.player.p.y);
	mlx_loop_hook(win.mlx_ptr, &keyhook, &win);
	mlx_image_to_window(win.mlx_ptr, win.img, 0, 0);
	mlx_loop(win.mlx_ptr);
	j = -1;
	while (win.map.elem[++j])
	{
		free(win.map.elem[j]);
	}
	free(win.map.elem);
	mlx_delete_image(win.mlx_ptr, win.img);
	mlx_terminate(win.mlx_ptr);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		ft_start(av[1]);
	else
		return (1);
}
