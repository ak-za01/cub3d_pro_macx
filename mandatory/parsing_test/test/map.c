/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:00:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/11 16:31:15 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Remove trailing newline from line */
static char	*trim_newline(char *line)
{
	int		len;
	char	*trimmed;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len > 0 && line[len - 1] == '\r')
		len--;
	trimmed = ft_substr(line, 0, len);
	return (trimmed);
}

/* Reallocate grid to add new line */
static char	**realloc_grid(char **old_grid, int old_height, int new_height)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (new_height + 1));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < old_height)
	{
		new_grid[i] = old_grid[i];
		i++;
	}
	new_grid[new_height - 1] = NULL;
	new_grid[new_height] = NULL;
	if (old_grid)
		free(old_grid);
	return (new_grid);
}

/* Check if line is start of map */
int	is_map_line(char *line)
{
	int		i;
	int		has_content;

	if (!line || is_empty_line(line))
		return (0);
	i = 0;
	has_content = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			break;
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] != ' ')
			has_content = 1;
		i++;
	}
	return (has_content);
}

/* Store a single map line in the data structure */
int	store_map_line(t_data *data, char *line)
{
	char	*trimmed;
	int		line_len;

	if (!line || !data)
		return (0);
	trimmed = trim_newline(line);
	if (!trimmed)
	{
		print_error("Memory allocation failed");
		return (0);
	}
	line_len = ft_strlen(trimmed);
	if (line_len > data->map.width)
		data->map.width = line_len;
	data->map.grid = realloc_grid(data->map.grid, 
									data->map.height, 
									data->map.height + 1);
	if (!data->map.grid)
	{
		free(trimmed);
		print_error("Memory allocation failed");
		return (0);
	}
	data->map.grid[data->map.height] = trimmed;
	data->map.height++;
	return (1);
}