/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:40:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/11 16:31:05 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Check if all map characters are valid */
int	check_map_characters(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			if (!is_map_char(data->map.grid[i][j]))
			{
				print_error("Invalid character in map");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/* Find player position and orientation */
int	find_player(t_data *data)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			if (data->map.grid[i][j] == 'N' || data->map.grid[i][j] == 'S' ||
				data->map.grid[i][j] == 'E' || data->map.grid[i][j] == 'W')
			{
				player_count++;
				data->player.pos_x = j + 0.5;
				data->player.pos_y = i + 0.5;
				data->player.orientation = data->map.grid[i][j];
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
	{
		print_error("No player found in map");
		return (0);
	}
	if (player_count > 1)
	{
		print_error("Multiple players found in map");
		return (0);
	}
	return (1);
}

/* Get character at position (handles out of bounds and short lines) */
static char	get_char_at(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map.height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(data->map.grid[y]))
		return (' ');
	return (data->map.grid[y][x]);
}

/* Check if position is valid (not space or out of bounds) */
static int	is_valid_pos(char c)
{
	return (c == '0' || c == '1' || c == 'N' || 
			c == 'S' || c == 'E' || c == 'W');
}

/* Check if a walkable position is properly surrounded */
static int	check_surrounded(t_data *data, int y, int x)
{
	char	c;
	int		dy;
	int		dx;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dy == 0 && dx == 0)
			{
				dx++;
				continue;
			}
			c = get_char_at(data, y + dy, x + dx);
			if (!is_valid_pos(c))
			{
				print_error("Map not closed (space or void near walkable area)");
				return (0);
			}
			dx++;
		}
		dy++;
	}
	return (1);
}

/* Check if map is closed/surrounded by walls */
int	check_map_closed(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			c = data->map.grid[i][j];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!check_surrounded(data, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/* Main map validation function */
int	validate_map(t_data *data)
{
	if (!data || !data->map.grid)
	{
		print_error("No map data");
		return (0);
	}
	if (data->map.height == 0 || data->map.width == 0)
	{
		print_error("Empty map");
		return (0);
	}
	if (!check_map_characters(data))
		return (0);
	if (!find_player(data))
		return (0);
	if (!check_map_closed(data))
		return (0);
	return (1);
}