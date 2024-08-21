/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:34:51 by lfarhi            #+#    #+#             */
/*   Updated: 2024/07/08 17:56:57 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	reset_path(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j].tileset == 0)
				game->map.grid[i][j++].path_f = INT_MAX;
			else
				game->map.grid[i][j++].path_f = INT_MIN;
		}
		i++;
	}
}

/*void print_path(t_game *game)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j].path_f == INT_MAX)
				printf(" # ");
			else if (game->map.grid[i][j].path_f == INT_MIN)
				printf(" X ");
			else
				printf("%2d ", game->map.grid[i][j].path_f);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n\n");
}*/

static t_bool	solve(t_game *game, t_vector2 pos, t_vector2 dest, int pathf)
{
	t_bool	v;

	v = FAILURE;
	if (pos.x < 0 || pos.y < 0 || pos.x >= (int)game->map.width
		|| pos.y >= (int)game->map.height)
		return (FAILURE);
	if (game->map.grid[pos.y][pos.x].tileset != 0)
		return (FAILURE);
	if (game->map.grid[pos.y][pos.x].path_f == INT_MIN)
		return (FAILURE);
	if (game->map.grid[pos.y][pos.x].path_f <= pathf)
		return (FAILURE);
	game->map.grid[pos.y][pos.x].path_f = pathf;
	if (pos.x == dest.x && pos.y == dest.y)
		return (SUCCESS);
	v = solve(game, (t_vector2){pos.x + 1, pos.y}, dest, pathf + 1) | v;
	v = solve(game, (t_vector2){pos.x - 1, pos.y}, dest, pathf + 1) | v;
	v = solve(game, (t_vector2){pos.x, pos.y + 1}, dest, pathf + 1) | v;
	v = solve(game, (t_vector2){pos.x, pos.y - 1}, dest, pathf + 1) | v;
	return (v);
}

static void	check_move(t_game *game,
	t_vector2 last_dir[2], int *min, t_vector2 *dest)
{
	t_vector2	last;
	t_vector2	dir;

	last = last_dir[0];
	dir = last_dir[1];
	if (last.x + dir.x >= 0
		&& last.x + dir.x < (int)game->map.width
		&& last.y + dir.y >= 0
		&& last.y + dir.y < (int)game->map.height)
	{
		if (game->map.grid[last.y + dir.y][last.x + dir.x].path_f < *min
			&& game->map.grid[last.y + dir.y][last.x + dir.x].path_f != INT_MIN)
		{
			*min = game->map.grid[last.y + dir.y][last.x + dir.x].path_f;
			*dest = (t_vector2){last.x + dir.x, last.y + dir.y};
		}
	}
}

t_vector2	move_to(t_game *game, t_vector2 pos, t_vector2 dest)
{
	const t_vector2	dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int				min;
	int				i;
	t_vector2		last;

	if (!exists_path(game, pos, dest))
		return (pos);
	last = dest;
	while (pos.x != dest.x || pos.y != dest.y)
	{
		i = 0;
		last = dest;
		min = game->map.grid[last.y][last.x].path_f;
		while (i < 4)
			check_move(game, (t_vector2[2]){last, dir[i++]}, &min, &dest);
	}
	return (last);
}

t_bool	exists_path(t_game *game, t_vector2 pos, t_vector2 dest)
{
	reset_path(game);
	return (solve(game, pos, dest, 0));
}
