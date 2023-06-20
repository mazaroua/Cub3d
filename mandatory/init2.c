/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:32:45 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 18:38:51 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	put_player(t_cub *cub)
{
	cub->p_x *= S_SIZE ;
	cub->p_y *= S_SIZE;
	cub->p_x += S_SIZE / 2;
	cub->p_y += S_SIZE / 2;
	cub->door_index = 0;
	cub->door_row = 0;
	set_textures(cub);
	cast_all_rays(cub);
}

void	init_keys(t_cub *cub)
{
	cub->move_backward = 0;
	cub->move_forward = 0;
	cub->move_right = 0;
	cub->move_left = 0;
	cub->rotation_right = 0;
	cub->rotation_left = 0;
	cub->gun_key = 0;
}

int	key_up(int keycode, t_cub *cub)
{
	if (keycode == MOVE_FORWARD)
		cub->move_forward = 0;
	if (keycode == MOVE_BACKWARD)
		cub->move_backward = 0;
	if (keycode == MOVE_LEFT)
		cub->move_left = 0;
	if (keycode == MOVE_RIGHT)
		cub->move_right = 0;
	if (keycode == RIGHT_ROTATION)
		cub->rotation_right = 0;
	if (keycode == LEFT_ROTATION)
		cub->rotation_left = 0;
	return (0);
}
