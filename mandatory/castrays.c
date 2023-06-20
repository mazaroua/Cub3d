/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:40:28 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 21:32:59 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	is_wall(t_cub *cub, double x, double y)
{
	int	xx;
	int	yy;

	xx = (int)floor(x / S_SIZE);
	yy = (int)floor(y / S_SIZE);
	if (xx < 0 || xx > (cub->win_width / S_SIZE) - 1
		|| yy < 0 || yy > (cub->win_height / S_SIZE) - 1)
		return (-1);
	if (cub->map_2d[yy][xx] == '1')
		return (1);
	return (0);
}

double	cal_distance(double x1, double y1, double x2, double y2)
{
	double	deltax;
	double	deltay;

	deltax = fabs(x2 - x1);
	deltay = fabs(y2 - y1);
	return (sqrt(deltax * deltax + deltay * deltay));
}

void	intersections(double rayangle, t_cub *cub)
{
	double	dis_h;
	double	dis_v;

	cub->vert_line = false;
	cub->hori_line = false;
	horizontal_intersection(rayangle, cub);
	vertical_intersection(rayangle, cub);
	dis_h = cal_distance(cub->p_x, cub->p_y, cub->x_h, cub->y_h);
	dis_v = cal_distance(cub->p_x, cub->p_y, cub->x_v, cub->y_v);
	if (dis_h > dis_v)
	{
		cub->vert_line = true;
		cub->next_x = cub->x_v;
		cub->next_y = cub->y_v;
		cub->x_offset = (int)cub->y_v % S_SIZE;
	}
	else
	{
		cub->hori_line = true;
		cub->next_x = cub->x_h;
		cub->next_y = cub->y_h;
		cub->x_offset = (int)cub->x_h % S_SIZE;
	}
}

double	set_angle(double angle)
{
	if (angle > 2 * M_PI)
		angle -= (2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void	cast_all_rays(t_cub *cub)
{
	int		i;
	double	rayangle;

	rayangle = cub->angle - (FOV_AGL / 2);
	rayangle = set_angle(rayangle);
	i = 0;
	while (i < NUM_RAYS)
	{
		intersections(rayangle, cub);
		rayangle += FOV_AGL / (double)NUM_RAYS;
		rayangle = set_angle(rayangle);
		render_walls(rayangle, cub, i);
		i += 1;
	}
}
