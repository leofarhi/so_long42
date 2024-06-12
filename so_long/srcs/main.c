/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:18:08 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 18:56:57 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	print_error(char *msg)
{
	(void)msg;
	printf("Error: %s\n", msg);
	//TODO: Implement this function
	return (1);
}

void	print_map(t_map *map) // TODO: Remove this function
{
	printf("Height: %ld\n", map->height);
	printf("Width: %ld\n", map->width);
	for (size_t i = 0; i < map->height; i++)
	{
		for (size_t j = 0; j < map->width; j++)
		{
			printf("%c", map->grid[i][j].type);
		}
		printf("\n");
	}
}

int	main(int argc, char **argv)
{
	t_window	window;

	(void)argv;
	(void)argc;
	//if (argc != 2)
	//	return (print_error("Usage: ./so_long [map]"));
	window.mlx = mlx_init();
	window.width = 1920/2;
	window.height = 1080/2;
	window.win = mlx_new_window(window.mlx, window.width, window.height, "so_long");
	window.map.cam[0] = 250;
	window.map.cam[1] = 50;
	window.map.life = 3;
	window.step = 0;
	window.rythme = 0;
	window.map.entities = NULL;
	if (!window.mlx || !window.win)
		return (print_error("Failed to create window"));
	if (load_assets(&window))
		return (print_error("Failed to load assets"));//TODO Check memory leaks window
	parse_map(&window, "maps/test.ber");
	print_map(&window.map);
	mlx_key_hook(window.win, key_hook, &window);
	mlx_loop_hook(window.mlx, main_loop, &window);
	mlx_loop(window.mlx);
	return (0);
}
