/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:53:54 by noctis            #+#    #+#             */
/*   Updated: 2025/12/22 16:48:25 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_init_mlx_map(t_game *game)
{
	game->mlx.ptr_img = mlx_new_image(game->mlx.ptr, WIDTH, HEIGHT);
	if (!game->mlx.ptr_img)
		return (-1);
	game->mlx.id_img = mlx_image_to_window(game->mlx.ptr, game->mlx.ptr_img, 0,
			0);
	if (game->mlx.id_img == -1)
		return (-1);
	return (0);
}

int	ft_init_lvl(t_game *game, t_data *data)
{
	if (ft_init_mlx_map(game) == -1)
	{
		return (ft_destroy_lvl(game, data, 0), -1);
	}
	if (ft_init_textures(data) == -1)
	{
		return (ft_destroy_lvl(game, data, 2), -1);
	}
	{
		ft_draw_level_text(game);
	}
	return (0);
}
