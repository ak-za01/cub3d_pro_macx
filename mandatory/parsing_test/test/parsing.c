/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:45:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/11 18:20:06 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Check if line is a texture or color identifier */
int	is_element_line(char *line)
{
	char	*str;

	if (!line)
		return (0);
	str = skip_spaces(line);
	if (!str || !*str)
		return (0);
	if ((ft_strncmp(str, "NO", 2) == 0 && (str[2] == '\0' || ft_isspace(str[2]))) ||
		(ft_strncmp(str, "SO", 2) == 0 && (str[2] == '\0' || ft_isspace(str[2]))) ||
		(ft_strncmp(str, "WE", 2) == 0 && (str[2] == '\0' || ft_isspace(str[2]))) ||
		(ft_strncmp(str, "EA", 2) == 0 && (str[2] == '\0' || ft_isspace(str[2]))))
		return (1);
	if ((str[0] == 'F' && (str[1] == '\0' || ft_isspace(str[1]))) ||
		(str[0] == 'C' && (str[1] == '\0' || ft_isspace(str[1]))))
		return (1);
	return (0);
}

/* Parse elements (textures and colors) before map */
static int	parse_elements(int fd, t_data *data, char **first_map_line)
{
	char	*line;

	while ((line = get_next_line(fd)))
	{
		if (is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (is_map_line(line))
		{
			*first_map_line = line;
			return (1);
		}
		if (is_element_line(line))
		{
			if (is_texture_line(line))
			{
				if (!parse_texture_line(line, data))
				{
					free(line);
					return (0);
				}
			}
			else
			{
				if (!parse_color_line(line, data))
				{
					free(line);
					return (0);
				}
			}
		}
		else
		{
			free(line);
			print_error("Invalid line in file");
			return (0);
		}
		free(line);
	}
	print_error("No map found in file");
	return (0);
}

/* Validate that all elements were parsed before map */
static int	validate_elements_complete(t_data *data)
{
	if (!all_elements_parsed(data))
	{
		if (!data->parsed[ELEM_NO])
			print_error("Missing North texture (NO)");
		else if (!data->parsed[ELEM_SO])
			print_error("Missing South texture (SO)");
		else if (!data->parsed[ELEM_WE])
			print_error("Missing West texture (WE)");
		else if (!data->parsed[ELEM_EA])
			print_error("Missing East texture (EA)");
		else if (!data->parsed[ELEM_F])
			print_error("Missing Floor color (F)");
		else if (!data->parsed[ELEM_C])
			print_error("Missing Ceiling color (C)");
		return (0);
	}
	return (1);
}

/* Parse map - ensures no elements appear after map starts */
int	parse_map(int fd, t_data *data, char *first_line)
{
	char	*line;
	int		map_started;

	map_started = 0;
	if (first_line && !is_empty_line(first_line))
	{
		if (!store_map_line(data, first_line))
			return (0);
		map_started = 1;
	}
	while ((line = get_next_line(fd)))
	{
		if (map_started)
		{
			if (is_element_line(line))
			{
				free(line);
				print_error("Element identifier found inside map");
				return (0);
			}
			if (is_empty_line(line))
			{
				free(line);
				print_error("Empty line found inside map");
				return (0);
			}
			if (!is_map_line(line))
			{
				free(line);
				print_error("Invalid character in map");
				return (0);
			}
			if (!store_map_line(data, line))
			{
				free(line);
				return (0);
			}
		}
		else
		{
			if (is_empty_line(line))
			{
				free(line);
				continue;
			}
			if (!is_map_line(line))
			{
				free(line);
				print_error("Invalid line after elements");
				return (0);
			}
			if (!store_map_line(data, line))
			{
				free(line);
				return (0);
			}
			map_started = 1;
		}
		free(line);
	}
	if (!map_started || data->map.height == 0)
	{
		print_error("No valid map found");
		return (0);
	}
	return (1);
}

/* Main parsing function */
int	parse_file(char *filename, t_data *data)
{
	int		fd;
	char	*first_map_line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open file");
		return (0);
	}
	first_map_line = NULL;
	if (!parse_elements(fd, data, &first_map_line))
	{
		close(fd);
		return (0);
	}
	if (!validate_elements_complete(data))
	{
		free(first_map_line);
		close(fd);
		return (0);
	}
	if (!parse_map(fd, data, first_map_line))
	{
		free(first_map_line);
		close(fd);
		return (0);
	}
	free(first_map_line);
	close(fd);
	if (!validate_map(data))
		return (0);
	return (1);
}
