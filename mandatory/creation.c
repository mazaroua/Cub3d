/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:21:13 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 18:22:08 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	ft_close(t_cub *cub)
{
	release_all(cub, 'f');
	return (0);
}

bool	check_wall(t_cub *cub, int x, int y)
{
	int	fpx;
	int	fpy;

	fpx = (int)floor(x) / S_SIZE;
	fpy = (int)floor(y) / S_SIZE;
	if (fpx < 0 || fpx > cub->win_width
		|| fpy < 0 || fpy > cub->win_height)
		return (true);
	if (cub->map_2d[fpy][fpx] == '1')
		return (true);
	return (false);
}

void	creation(t_cub *cub)
{
	init_values(cub);
	init_keys(cub);
	cub->w_ptr = mlx_new_window(cub->m_ptr, WIN_WIDTH, WIN_HEIGTH, "cub3d");
	cub->data->img = mlx_new_image(cub->m_ptr, WIN_WIDTH, WIN_HEIGTH);
	cub->data->addr = mlx_get_data_addr(cub->data->img, \
	&cub->data->bits_per_pixel, &cub->data->line_length, &cub->data->endian);
	put_surfaces(cub);
	put_player(cub);
	mlx_hook(cub->w_ptr, 2, 0, ft_move, cub);
	mlx_hook(cub->w_ptr, 3, 0, key_up, cub);
	mlx_hook(cub->w_ptr, 17, 0, ft_close, cub);
	mlx_loop_hook(cub->m_ptr, keys, cub);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
	mlx_loop(cub->m_ptr);
}
