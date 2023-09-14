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
#define WIDTH 1000
#define HEIGHT 10000

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
			mlx_put_pixel(img, start.x + j, start.y + i, color);
			j++;
		}
		i++;
	}
}

t_point	player_drawer(mlx_image_t *img, t_point pos, t_point player,  int color)
{
	int	r;
	float deg;

	r = -1;
	deg = 0;
	if(player.x != 0 || player.y != 0)
		pos = player;
	while(++r < 25)
		mlx_put_pixel(img, pos.x + 25 ,pos.y + 25 + r, color);
	r = 0;
	while(r < 11)
	{
		deg = 0;
		while (deg < M_PI * 2)
		{
			mlx_put_pixel(img, pos.x + 25 + r * cos(deg),
				pos.y + 25 + r * sin(deg), color);
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
	end = assign_point(win->map.wide * 50 + 20, win->map.width * 50 + 20, 0);
	cub_drawer(win->img, start, end, 0x909090FF);
	end = assign_point(50, 50, 0);
	while (++i < win->map.wide)
	{
		j = -1;
		while (++j < 9)
		{
			start = assign_point(j * 50 + 10, i * 50 + 10, 0);
			if (matrix[i][j] == '1')
				cub_drawer(win->img, start, end, 0x09005EFF);
			else
				cub_drawer(win->img, start, end, 0xB8A649FF);
		}
	}
	player = player_drawer(win->img, start, player, 0xFF322BFF);
	return(player);
}

int check_inside(t_window *win, t_point *player)
{
	int i;
	int j;

	i = (player->x) / 50;
	j = (player->y) / 50;
	if(win->map.elem[j][i] == '1')
	{
		if(win->map.elem[j + 1][i] == '1')
			player->x--;
		if(win->map.elem[j][i + 1] == '1')
			player->x--;
		return(0);
	}
	else
	{
		return(1);
	}
}

void	keyhook(void *param)
{
	t_window	*win = (t_window *)param;
	t_point		start;
	//t_point		end;
	int			i;

	mlx_delete_image(win->mlx_ptr, win->img);
	//printf("x=%d,y=%d",win->player.p.x, win->player.p.y);
	win->img = mlx_new_image(win->mlx_ptr, win->map.width * 50 + 20, win->map.wide * 50 + 20);
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_S) && check_inside(win, &win->player.p))
	{
		win->player.p.x -= cos(win->player.angle * M_PI / 180);
		win->player.p.y -= sin(win->player.angle * M_PI / 180);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_W) && check_inside(win, &win->player.p))
	{
		win->player.p.x += cos(win->player.angle * M_PI / 180);
		win->player.p.y += sin(win->player.angle * M_PI / 180);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_D) && check_inside(win, &win->player.p))
	{
		win->player.p.x -= sin(win->player.angle * M_PI / 180);
		win->player.p.y += cos(win->player.angle * M_PI / 180);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_A) && check_inside(win, &win->player.p))
	{
		win->player.p.x += sin(win->player.angle * M_PI / 180);
		win->player.p.y -= cos(win->player.angle * M_PI / 180);
	}
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_RIGHT))
		win->player.angle++;
	if (mlx_is_key_down(win->mlx_ptr, MLX_KEY_LEFT))
		win->player.angle--;
	win->player.p = ft_draw_map(win, win->map.elem, win->player.p);
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
	int j;
	int fd = open(str, O_RDWR);
	char *dtr;
	int	dtrsize = 0;
	win.map.wide = 0;
	win.map.width = 0;
	while(1)
	{
		dtr = get_next_line(fd);
		if(dtr == NULL)
			break;
			dtrsize++;
	}
	close(fd);
	fd = open(str, O_RDWR);

	// win.map.wide = 0;
	win.map.elem = (char **)ft_calloc(dtrsize + 1, sizeof(char *));
	win.map.elem[win.map.wide] = get_next_line(fd);
	while (win.map.elem[win.map.wide])
	{
		if(ft_strlen(win.map.elem[win.map.wide]) > win.map.width)
			win.map.width = ft_strlen(win.map.elem[win.map.wide]);
		printf("%s", win.map.elem[win.map.wide]);
		win.map.wide++;//map win.map.width * 50 + 20
		win.map.elem[win.map.wide] = get_next_line(fd);
	}
	win.map.width--;//map biggest width
	win.mlx_ptr = mlx_init(win.map.width * 50 + 20, win.map.wide * 50 + 20, "Test", true);
	if (!win.mlx_ptr)
		error();
	win.img = mlx_new_image(win.mlx_ptr, win.map.width * 50 + 20, win.map.wide * 50 + 20);
	if (!win.img)
		error();
	win.player.p = assign_point(310, 60, 0); 
	win.player.p = ft_draw_map(&win, win.map.elem, win.player.p);
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


