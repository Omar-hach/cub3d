/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:58:11 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/26 22:49:39 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include "MLX42/MLX42.h"
#define WIDTH 250
#define HEIGHT 250

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
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
	mlx_image_t *wall = mlx_texture_to_image(mlx, walltext);
	if (!wall)
		error();
	mlx_image_t *back = mlx_texture_to_image(mlx, backtext);
	if (!back)
		error();
	mlx_image_t *player = mlx_texture_to_image(mlx, playertext);
	if (!player)
		error();
	// Display the image
	i = 0;
	int j = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if(strs[i][j] == '1')
				mlx_image_to_window(mlx, wall, i * 50, j * 50);
			else if(strs[i][j] == '0')
				mlx_image_to_window(mlx, back, i * 50, j * 50);
			else if (strs[i][j] == 'P')
			{
				mlx_image_to_window(mlx, player, i * 50, j * 50);
			}
			
			j++;
		}
		i++;
	}

	mlx_loop(mlx);

	mlx_delete_image(mlx, wall);
	mlx_delete_image(mlx, back);
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