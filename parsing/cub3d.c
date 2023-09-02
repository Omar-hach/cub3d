/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:58:11 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/28 12:00:05 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
// #include "MLX42/MLX42.h"
#define WIDTH 1000
#define HEIGHT 1000
// void my_keyhook(mlx_key_data_t keydata, void* param)
// {
// 	static int i;
// 	static int j;
// 	// If we PRESS the 'J' key, print "Hello".
// 	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
// 	{
// 					mlx_put_pixel((mlx_image_t *)param, i, j, 0xFF0000FF);
// 					j = j + 10;
// 					i = i + 10;	
// 	}
// 	// If we RELEASE the 'K' key, print "World".

// }

void	cub_drawer(mlx_image_t *wall, int startx, int starty, int endx, int endy, int color)
{
	int i = startx;
	int j = starty;
	while(i < endx)
	{
		j = starty;
		while(j < endy)
		{
			mlx_put_pixel(wall, i, j, color);
			j++;
		}
		i++;
	}
}
void	player_drawer(mlx_image_t *wall, int startx, int starty, int radius, int color)
{
	int	deg = 0;
	int i = startx + radius * cos(deg);
	int j = starty + radius * sin(deg);
	
	while(radius > 0)
	{
		deg = 0;
		while(deg < 360)
		{	
			i = startx + radius * cos(deg);
			j = starty + radius * sin(deg);
			mlx_put_pixel(wall, i, j, color);
			deg++;
		}
		radius--;
	}
}


// Exit the program as failure.
/*static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}*/
static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
// Print the window width and height.
void ft_start(char *str)
{
	char **strs = malloc(100 * sizeof(char *));
	int i = 0;
	int fd = open(str, O_RDWR);
	while (1)
	{
		strs[i] = get_next_line(fd);
		if (strs[i] == NULL)
			break;
		printf("%s\n", strs[i]);
		i++;
	}
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
		error();

	// Try to load the file
	mlx_texture_t *walltext = mlx_load_png("Untitled.png");
	if (!walltext)
		error();
	mlx_texture_t *backtext = mlx_load_png("back.png");
	if (!walltext)
		error();
	mlx_texture_t *playertext = mlx_load_png("player.png");
	if (!playertext)
		error();
	// Convert texture to a displayable image
	mlx_image_t *wall = mlx_new_image(mlx, WIDTH, HEIGHT);
	// mlx_image_t *wall = mlx_texture_to_image(mlx, walltext);
	// if (!wall)
	// 	error();
	// mlx_image_t *back = mlx_texture_to_image(mlx, backtext);
	// if (!back)
	// 	error();
	// mlx_image_t *player = mlx_texture_to_image(mlx, playertext);
	// if (!player)
	// 	error();

	// Display the image
	i = 0;
	int j = 0;
	int playerx = 0;
	int playery = 0;
	while (strs[i])
	{
		j = 0;

		while (strs[i][j])
		{
			// mlx_key_hook(mlx, &my_keyhook, back);
			if (strs[i][j] == '1')
				cub_drawer(wall, j * 50, i * 50, (j +1) * 50, (i + 1) * 50, 0x000000FF);
			else if (strs[i][j] == '0')
				cub_drawer(wall, j * 50, i * 50, (j +1) * 50, (i + 1) * 50, 0xFFFFFFFF);
			else if (strs[i][j] == 'P')
			{
				cub_drawer(wall, j * 50, i * 50, (j +1) * 50, (i + 1) * 50, 0xFFFFFFFF);
				playery = i * 50;
				playerx = j * 50;
			}
				
			// if (strs[i][j] == '1')
			// 	mlx_image_to_window(mlx, wall, i * 50, j * 50);
			// else if (strs[i][j] == '0')
			// 	mlx_image_to_window(mlx, back, i * 50, j * 50);
			// else if (strs[i][j] == 'P')
			// {
			// 	mlx_image_to_window(mlx, player, i * 50, j * 50);
			// }
			j++;
		}
		i++;
	}
	player_drawer(wall, playerx, playery, 10, 0xFF0000FF);
	mlx_image_to_window(mlx, wall, 0, 0);
	mlx_loop(mlx);

	mlx_delete_image(mlx, wall);
	// mlx_delete_image(mlx, back);
	mlx_delete_texture(walltext);
	mlx_delete_texture(backtext);

	// Optional, terminate will clean up any leftover images (not textures!)
	mlx_terminate(mlx);
}

int main(int ac, char **av)
{
	if (ac == 2)
		ft_start(av[1]);
}