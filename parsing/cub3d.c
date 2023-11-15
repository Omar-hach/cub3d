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

// static void ft_error(void)
//
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

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
		ft_start(i, strs);
	}
	else
		return (1);
}

