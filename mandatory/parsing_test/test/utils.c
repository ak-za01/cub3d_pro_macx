/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:20:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/11 17:47:03 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Check if character is whitespace */
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/* Check if line is empty (only whitespace) */
int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Skip leading spaces and return pointer to first non-space */
char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

/* Check if character is valid in map */
int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || 
			c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

/* Check file extension */
int	check_extension(char *filename)
{
	char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	if (strcmp(dot, ".cub") != 0)
		return (0);
	return (1);
}


/* Check if file exists and is readable */
int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

/* Safe atoi with error detection */
int	ft_atoi_safe(char *str, int *error)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	*error = 0;
	if (!str || !*str)
	{
		*error = 1;
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			*error = 1;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		if (result > 255)
		{
			*error = 1;
			return (0);
		}
		i++;
	}
	return ((int)result);
}

/* Print error message */
void	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

/* Exit with error message and cleanup */
void	exit_error(char *msg, t_data *data)
{
	print_error(msg);
	free_data(data);
	exit(1);
}

/* Free map grid */
void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
}

/* Free all allocated data */
void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return;
	i = 0;
	while (i < TEX_COUNT)
	{
		if (data->textures[i])
		{
			free(data->textures[i]);
			data->textures[i] = NULL;
		}
		i++;
	}
	free_map(&data->map);
}