/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:30:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/11 16:31:19 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Extract and validate texture path from line */
static char	*extract_texture_path(char *line)
{
	char	*path;
	char	*start;
	char	*end;

	start = skip_spaces(line);
	if (!start || !*start)
		return (NULL);
	end = start;
	while (*end && *end != '\n' && *end != '\r')
		end++;
	end--;
	while (end > start && ft_isspace(*end))
		end--;
	end++;
	path = ft_substr(start, 0, end - start);
	if (!path)
		return (NULL);
	return (path);
}

/* Get texture index and element index from identifier */
static int	get_texture_index(char *identifier, int *tex_idx, int *elem_idx)
{
	if (ft_strncmp(identifier, "NO", 2) == 0 && 
		(identifier[2] == '\0' || ft_isspace(identifier[2])))
	{
		*tex_idx = NORTH;
		*elem_idx = ELEM_NO;
		return (1);
	}
	else if (ft_strncmp(identifier, "SO", 2) == 0 && 
		(identifier[2] == '\0' || ft_isspace(identifier[2])))
	{
		*tex_idx = SOUTH;
		*elem_idx = ELEM_SO;
		return (1);
	}
	else if (ft_strncmp(identifier, "WE", 2) == 0 && 
		(identifier[2] == '\0' || ft_isspace(identifier[2])))
	{
		*tex_idx = WEST;
		*elem_idx = ELEM_WE;
		return (1);
	}
	else if (ft_strncmp(identifier, "EA", 2) == 0 && 
		(identifier[2] == '\0' || ft_isspace(identifier[2])))
	{
		*tex_idx = EAST;
		*elem_idx = ELEM_EA;
		return (1);
	}
	return (0);
}

/* Set texture in data structure */
static int	set_texture(t_data *data, int tex_idx, int elem_idx, char *path)
{
	if (data->parsed[elem_idx])
	{
		free(path);
		print_error("Duplicate texture identifier");
		return (0);
	}
	if (!file_exists(path))
	{
		free(path);
		print_error("Texture file does not exist or is not readable");
		return (0);
	}
	data->textures[tex_idx] = path;
	data->parsed[elem_idx] = 1;
	return (1);
}

/* Parse texture line (NO, SO, WE, EA) */
int	parse_texture_line(char *line, t_data *data)
{
	char	*identifier;
	char	*path;
	int		tex_idx;
	int		elem_idx;

	if (!line || !data)
		return (0);
	identifier = skip_spaces(line);
	if (!identifier || !*identifier)
		return (0);
	if (!get_texture_index(identifier, &tex_idx, &elem_idx))
		return (0);
	identifier += 2;
	identifier = skip_spaces(identifier);
	path = extract_texture_path(identifier);
	if (!path)
	{
		print_error("Invalid texture path");
		return (0);
	}
	return (set_texture(data, tex_idx, elem_idx, path));
}

/* Check if line starts with texture identifier */
int	is_texture_line(char *line)
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
	return (0);
}