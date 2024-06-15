/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:25:08 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 19:25:08 by lfarhi           ###   ########.fr       */
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

int main()
{
	t_window	*window;
	t_game		game;

	window = mlxe_init(1920/2, 1080/2, "so_long");
	if (!window)
		return (print_error("Error : Failed to initialize window"));
	game.window = window;
	load_assets(&game);//TODO Check if loading is successful
	parse_map(&game, "maps/test.ber");//TODO Check if loading is successful
	mlxe_loop(window, menu_loop, &game);
	free_map(&game);
	mlxe_destroy(window);
	return (0);
}
