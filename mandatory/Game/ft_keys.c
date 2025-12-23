/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:57:21 by noctis            #+#    #+#             */
/*   Updated: 2025/12/22 19:19:46 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_capture_keys(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	t_data	*data;

	(void)keydata;
	game = (t_game *)param;
	data = &game->c_lvl->data;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx.ptr);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_L))
	{
		ft_lock_and_unlock_cam(game);
	}
}

void	ft_lock_and_unlock_cam(t_game *game)
{
	if (game->lock_cam == 0)
	{
		mlx_set_cursor_mode(game->mlx.ptr, MLX_MOUSE_NORMAL);
		game->lock_cam = 1;
	}
	else
	{
		mlx_set_cursor_mode(game->mlx.ptr, MLX_MOUSE_DISABLED);
		game->lock_cam = 0;
	}
}
