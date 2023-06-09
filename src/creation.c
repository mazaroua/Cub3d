#include "../inc/cub.h"

bool	check_wall(t_cub *cub)
{
	int	fpx;
	int	fpy;

	fpx = (int)floor(cub->p_x) / 32;
	fpy = (int)floor(cub->p_y) / 32;
	if (cub->map_2d[fpy][fpx] == '1')
		return (true);
	return (false);
}

void put_square(t_cub *cub, int x, int y, int color)
{
	int i;
	int j;

	j = 0;
	while (j < S_SIZE * SCALE_SIZE)
	{
		i = 0;
		while (i < S_SIZE * SCALE_SIZE)
		{
			my_mlx_pixel_put(cub,  x + i, y + j, color);
			i += 1;
		}
		j += 1;
	}
}

void draw_mini_map(t_cub *cub)
{
	int x;
	int y;
	int cofx;
	int cofy;

	y = 0;
	while (cub->map_2d[y])
	{
		x = 0;
		cofy = (y * S_SIZE) * SCALE_SIZE;
		cofx = 0;
		x = 0;
		while (cub->map_2d[y][x])
		{
			if (x > 0)
				cofx = (x * S_SIZE) * SCALE_SIZE;
			if (cub->map_2d[y][x] == '1')
				put_square(cub, cofx, cofy, 0xffffff);
			else
				put_square(cub, cofx, cofy, 0x000000);
			x += 1;
		}
		y += 1;
	}
}

void put_player(t_cub *cub)
{
	cub->p_x *= S_SIZE ;
	cub->p_y *= S_SIZE;
	cub->p_x += S_SIZE / 2;
	cub->p_y += S_SIZE / 2;
	cub->p_minix = cub->p_x * SCALE_SIZE;
	cub->p_miniy = cub->p_y * SCALE_SIZE;
	put_square(cub, cub->p_minix, cub->p_miniy, 0xff0000);
	set_textures(cub);
	draw_mini_map(cub);
	cast_all_rays(cub);
}

void creation(t_cub *cub)
{
	init_values(cub);
	cub->w_ptr = mlx_new_window(cub->m_ptr, cub->win_width, cub->win_height, "cub3d");
	cub->data->img = mlx_new_image(cub->m_ptr, 1600, 900);
	cub->data->addr = mlx_get_data_addr(cub->data->img, &cub->data->bits_per_pixel \
	, &cub->data->line_length, &cub->data->endian);
	put_surfaces(cub);
	put_player(cub);
	mlx_hook(cub->w_ptr, 02, (1L << 0), ft_move, cub);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
	mlx_loop(cub->m_ptr);
}