/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:30:10 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 18:30:12 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	back_and_for(t_cub *cub, int key)
{
	if (key == MOVE_FORWARD)
	{
		cub->p_x += 3 * cos(cub->angle);
		cub->p_y += 3 * sin(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
	if (key == MOVE_BACKWARD)
	{
		cub->p_x -= 3 * cos(cub->angle);
		cub->p_y -= 3 * sin(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
}

void	player_newpos(t_cub *cub, int key)
{
	back_and_for(cub, key);
	if (key == MOVE_LEFT)
	{
		cub->p_x += 3 * sin(cub->angle);
		cub->p_y -= 3 * cos(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
	if (key == MOVE_RIGHT)
	{
		cub->p_x -= 3 * sin(cub->angle);
		cub->p_y += 3 * cos(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
}

bool	check_sides(t_cub *cub, int xtmp, int ytmp)
{
	double	right_angle;
	double	left_angle;

	right_angle = set_angle(cub->angle - M_PI / 2);
	intersections(right_angle, cub);
	if (cal_distance(cub->p_x, cub->p_y, cub->next_x, cub->next_y) < 2)
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
		return (true);
	}
	left_angle = set_angle(cub->angle + M_PI / 2);
	intersections(left_angle, cub);
	if (cal_distance(cub->p_x, cub->p_y, cub->next_x, cub->next_y) < 2)
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
		return (true);
	}
	return (false);
}
