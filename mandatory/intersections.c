/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:28:45 by mazaroua          #+#    #+#             */
/*   Updated: 2023/06/21 00:33:33 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	first_horizontal_intersection(double rayangle, t_cub *cub)
{
	if (player_up(rayangle))
	{
		cub->y_h = floor(cub->p_y / S_SIZE) * S_SIZE;
	}
	else
		cub->y_h = floor(cub->p_y / S_SIZE) * S_SIZE + S_SIZE;
	cub->x_h = (cub->y_h - cub->p_y) / tan(rayangle) + cub->p_x;
}

void	next_horizontal_intersection(double rayangle, t_cub *cub)
{
	if (player_up(rayangle))
	{
		cub->y_h -= S_SIZE;
		cub->x_h += (-S_SIZE / tan(rayangle));
	}
	else
	{
		cub->y_h += S_SIZE;
		cub->x_h += (S_SIZE / tan(rayangle));
	}
}

void	horizontal_intersection(double rayangle, t_cub *cub)
{
	first_horizontal_intersection(rayangle, cub);
	if (!is_wall(cub, cub->x_h, cub->y_h + 1)
		&& !is_wall(cub, cub->x_h, cub->y_h - 1))
	{
		while (true)
		{
			next_horizontal_intersection(rayangle, cub);
			if (is_wall(cub, cub->x_h, cub->y_h + 1)
				|| is_wall(cub, cub->x_h, cub->y_h - 1))
				break ;
		}
	}
}

void	first_ver_intersect(double rayangle, t_cub *cub)
{
	double	y1;
	double	xdiff;

	if (right_side(rayangle))
		cub->x_v = (floor(cub->p_x / S_SIZE) + 1) * S_SIZE;
	else
		cub->x_v = floor(cub->p_x / S_SIZE) * S_SIZE;
	xdiff = cub->x_v - cub->p_x;
	y1 = xdiff * tan(rayangle);
	cub->y_v = cub->p_y + y1;
}

void	next_ver_intersect(double rayangle, t_cub *cub)
{
	if (right_side(rayangle))
	{
		cub->x_v += S_SIZE;
		cub->y_v += (S_SIZE * tan(rayangle));
	}
	else
	{
		cub->x_v -= S_SIZE;
		cub->y_v += (-S_SIZE * tan(rayangle));
	}
}

void	vertical_intersection(double rayangle, t_cub *cub)
{
	first_ver_intersect(rayangle, cub);
	if (!is_wall(cub, cub->x_v + 1, cub->y_v)
		&& !is_wall(cub, cub->x_v - 1, cub->y_v))
	{
		while (true)
		{
			next_ver_intersect(rayangle, cub);
			if (is_wall(cub, cub->x_v + 1, cub->y_v)
				|| is_wall(cub, cub->x_v - 1, cub->y_v))
				break ;
		}
	}
}
