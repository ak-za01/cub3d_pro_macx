/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:30:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/11 16:30:57 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Free split array */
static void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/* Parse RGB values from string "R,G,B" */
int	parse_rgb(char *str, t_color *color)
{
	char	**rgb_split;
	int		error;
	int		count;

	if (!str || !color)
		return (0);
	rgb_split = ft_split(str, ',');
	if (!rgb_split)
		return (0);
	count = 0;
	while (rgb_split[count])
		count++;
	if (count != 3)
	{
		free_split(rgb_split);
		print_error("Color must have exactly 3 RGB values");
		return (0);
	}
	color->r = ft_atoi_safe(rgb_split[0], &error);
	if (error)
	{
		free_split(rgb_split);
		print_error("Invalid R value (must be 0-255)");
		return (0);
	}
	color->g = ft_atoi_safe(rgb_split[1], &error);
	if (error)
	{
		free_split(rgb_split);
		print_error("Invalid G value (must be 0-255)");
		return (0);
	}
	color->b = ft_atoi_safe(rgb_split[2], &error);
	if (error)
	{
		free_split(rgb_split);
		print_error("Invalid B value (must be 0-255)");
		return (0);
	}
	free_split(rgb_split);
	return (1);
}

/* Parse floor color line */
static int	parse_floor_color(char *line, t_data *data)
{
	char	*value_str;

	if (data->parsed[ELEM_F])
	{
		print_error("Duplicate floor color (F)");
		return (0);
	}
	value_str = skip_spaces(line + 1);
	if (!parse_rgb(value_str, &data->floor_color))
		return (0);
	data->parsed[ELEM_F] = 1;
	return (1);
}

/* Parse ceiling color line */
static int	parse_ceiling_color(char *line, t_data *data)
{
	char	*value_str;

	if (data->parsed[ELEM_C])
	{
		print_error("Duplicate ceiling color (C)");
		return (0);
	}
	value_str = skip_spaces(line + 1);
	if (!parse_rgb(value_str, &data->ceiling_color))
		return (0);
	data->parsed[ELEM_C] = 1;
	return (1);
}

/* Parse color line (F or C) */
int	parse_color_line(char *line, t_data *data)
{
	char	*str;

	if (!line || !data)
		return (0);
	str = skip_spaces(line);
	if (!str || !*str)
		return (0);
	if (str[0] == 'F' && (str[1] == '\0' || ft_isspace(str[1])))
		return (parse_floor_color(str, data));
	else if (str[0] == 'C' && (str[1] == '\0' || ft_isspace(str[1])))
		return (parse_ceiling_color(str, data));
	return (0);
}