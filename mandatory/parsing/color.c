/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 08:03:13 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/12 20:05:13 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_floor_color(char *line, t_data *data)
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

int	parse_ceiling_color(char *line, t_data *data)
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
