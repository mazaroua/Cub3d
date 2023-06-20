/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:37:34 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 17:37:58 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

char	poss_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'W')
		return (WEST);
	if (c == 'E')
		return (EAST);
	return (0);
}

void	check_map(char **map, t_cub *cub, int i)
{
	int		j;
	bool	pos;

	pos = false;
	if (!*map)
		exit_error(cub, 3);
	while (map[++i])
	{
		j = (-1);
		while (map[i][++j])
		{
			if (poss_char(map[i][j]) == 0)
				exit_error(cub, 3);
			if (pos == true && poss_char(map[i][j]) != 1)
				exit_error(cub, 3);
			if (poss_char(map[i][j]) != 1)
			{
				cub->p_or = poss_char(map[i][j]);
				cub->p_x = j;
				cub->p_y = i;
				pos = true;
			}
		}
	}	
}
