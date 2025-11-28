/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:18:20 by anktiri           #+#    #+#             */
/*   Updated: 2025/11/28 23:25:38 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_lvl_line(char *line)
{
	if (ft_strncmp(line, "LV", 2) == 0 && (line[2] == '\0' || ft_isspace(line[2])))
		return (1);
	return (0);
}

int		parse_lvl_line(char *line, t_data *data)
{
	parse_texture_line(line, data, 1);
	if (!check_file(data->next_file, 3))
	{
		print_error("LV file does not exist or is not readable");
		return (0);
	}
	return (1);
}

t_data	*last(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back(t_data **lst, t_data *new)
{
	t_data	*ptr;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = last(*lst);
	ptr->next = new;
	new->next = NULL;
}

void	free_list(t_data *head)
{
	t_data	*tmp;

	while (head)
	{
		tmp = head->next;
		free_data(head);
		free(head);
		head = tmp;
	}
}
