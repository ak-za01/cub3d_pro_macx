/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 02:27:17 by akzaza            #+#    #+#             */
/*   Updated: 2025/12/12 02:27:21 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	display_frame(t_game *game)
{
	char			*num;
	char			*path;
	mlx_texture_t	*tex;

	if (game->stage_anim.current_img)
		mlx_delete_image(game->mlx.ptr, game->stage_anim.current_img);
	num = ft_itoa(game->stage_anim.current_frame + 1);
	path = ft_strjoin(game->stage_anim.folder, num);
	free(num);
	num = ft_strjoin(path, ".png");
	free(path);
	tex = mlx_load_png(num);
	free(num);
	if (!tex)
		return ;
	game->stage_anim.current_img = mlx_texture_to_image(game->mlx.ptr, tex);
	mlx_resize_image(game->stage_anim.current_img, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx.ptr, game->stage_anim.current_img, 0, 0);
	mlx_delete_texture(tex);
}

static void	handle_space_key(t_game *game)
{
	if (game->stage_anim.stage == 1)
	{
		ft_strlcpy(game->stage_anim.folder, 
			"mandatory/animation/Loading_animation/loading_screen", 256);
		game->stage_anim.total_frames = 8;
		game->stage_anim.frame_delay = 20;
		game->stage_anim.current_frame = 0;
		game->stage_anim.stage = 2;
	}
	else if (game->stage_anim.stage == 3)
		mlx_close_window(game->mlx.ptr);
}

void	update_stage_animation(t_game *game)
{
	if (!game->stage_anim.is_active)
		return ;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_SPACE))
	{
		handle_space_key(game);
		return ;
	}
	if (++game->stage_anim.frame_counter >= game->stage_anim.frame_delay)
	{
		game->stage_anim.frame_counter = 0;
		display_frame(game);
		if (++game->stage_anim.current_frame >= game->stage_anim.total_frames)
		{
			if (game->stage_anim.stage == 2)
			{
				game->stage_anim.is_active = 0;
				if (game->stage_anim.current_img)
					mlx_delete_image(game->mlx.ptr, game->stage_anim.current_img);
			}
			else
				game->stage_anim.current_frame = 0;
		}
	}
}