/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:36:55 by noctis            #+#    #+#             */
/*   Updated: 2025/12/12 02:27:38 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	start_animation(t_game *game, char *folder, int frames, int delay, int stage)
{
	ft_strlcpy(game->stage_anim.folder, folder, 256);
	game->stage_anim.total_frames = frames;
	game->stage_anim.current_frame = 0;
	game->stage_anim.frame_counter = 0;
	game->stage_anim.frame_delay = delay;
	game->stage_anim.is_active = 1;
	game->stage_anim.current_img = NULL;
	game->stage_anim.stage = stage;
}

void	ft_start_animation(t_game *game, t_data *data)
{
	(void)data;
	// start_animation(game,
	// 	"mandatory/animation/complete_animation/complete_animation", 8, 15);
}

void	ft_switch_animation(t_game *game, t_data *data)
{
	(void)data;
	start_animation(game,
		"mandatory/animation/stage_complete/stage_complete", 8, 20, 1);
}

void	ft_dead_animation(t_game *game, t_data *data)
{
	(void)data;
	// start_animation(game,
	// 	"mandatory/animation/failed_animation/failed_animation", 8, 8);
}

void	ft_end_animation(t_game *game, t_data *data)
{
	(void)data;
	start_animation(game,
		"mandatory/animation/complete_animation/complete_animation", 6, 30, 3);
}