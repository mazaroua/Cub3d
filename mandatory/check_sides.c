/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sides.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:33:21 by mazaroua          #+#    #+#             */
/*   Updated: 2023/06/20 21:34:15 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

bool	right_side(double rayangle)
{
	if ((rayangle > 3 * (M_PI / 2) && rayangle <= 2 * M_PI)
		|| (fabs(rayangle) >= 0 && rayangle < M_PI / 2))
		return (true);
	return (false);
}

int	player_up(double angle)
{
	if ((angle * (180 / M_PI)) > (double)180
		&& (angle * (180 / M_PI)) < (double)360)
		return (1);
	return (0);
}
