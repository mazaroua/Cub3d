/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:26:58 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 18:39:02 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	increment_angle(t_cub *cub, int keycode)
{
	if (keycode == RIGHT_ROTATION)
	{
		if (cub->angle >= 355 * (M_PI / 180))
		{
			cub->angle = 0;
			return ;
		}
		cub->angle = cub->angle * (180 / M_PI);
		cub->angle += 5;
		cub->angle = cub->angle * (M_PI / 180);
	}
	if (keycode == LEFT_ROTATION)
	{
		if (cub->angle <= 0)
		{
			cub->angle = 355 * (M_PI / 180);
			return ;
		}
		cub->angle = cub->angle * (180 / M_PI);
		cub->angle -= 5;
		cub->angle = cub->angle * (M_PI / 180);
	}
}

void	still_open(t_cub *cub)
{
	int	i;
	int	j;

	j = 0;
	while (cub->map_2d[j])
	{
		i = 0;
		while (cub->map_2d[j][i])
		{
			if (j != cub->door_row && i != cub->door_index
				&& cub->map_2d[j][i] == 'x')
				cub->map_2d[j][i] = 'D';
			i += 1;
		}
		j += 1;
	}
}

void	move_player(t_cub *cub, int keycode)
{
	int	xtmp;
	int	ytmp;

	xtmp = cub->p_x;
	ytmp = cub->p_y;
	player_newpos(cub, keycode);
	if (check_sides(cub, xtmp, ytmp) == true)
		return ;
	intersections(cub->angle, cub);
	if (cal_distance(cub->p_x, cub->p_y, cub->next_x, cub->next_y) < 6)
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
		return ;
	}
	if (check_wall(cub, cub->p_x, cub->p_y) == 1
		|| check_wall(cub, cub->p_x, cub->p_y) == 2)
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
	}
}

int	ft_move(int keycode, t_cub *cub)
{
	if (keycode == MOVE_FORWARD)
		cub->move_forward = 1;
	if (keycode == MOVE_BACKWARD)
		cub->move_backward = 1;
	if (keycode == MOVE_LEFT)
		cub->move_left = 1;
	if (keycode == MOVE_RIGHT)
		cub->move_right = 1;
	if (keycode == RIGHT_ROTATION)
		cub->rotation_right = 1;
	if (keycode == LEFT_ROTATION)
		cub->rotation_left = 1;
	if (keycode == ESC)
		release_all(cub, 'f');
	return (0);
}

int	keys(t_cub *cub)
{
	if (cub->move_forward == 1)
		move_player(cub, MOVE_FORWARD);
	if (cub->move_backward == 1)
		move_player(cub, MOVE_BACKWARD);
	if (cub->move_right == 1)
		move_player(cub, MOVE_RIGHT);
	if (cub->move_left == 1)
		move_player(cub, MOVE_LEFT);
	if (cub->rotation_right == 1)
		increment_angle(cub, RIGHT_ROTATION);
	if (cub->rotation_left == 1)
		increment_angle(cub, LEFT_ROTATION);
	put_surfaces(cub);
	cast_all_rays(cub);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, \
	cub->data->img, 0, 0);
	return (0);
}
