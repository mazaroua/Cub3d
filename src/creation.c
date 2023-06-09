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
	while (j < M_SIZE)
	{
		i = 0;
		while (i < 7)
		{
			my_mlx_pixel_put(cub,  x + i, y + j, color);
			if (!(i % M_SIZE) || !(j % M_SIZE))
				my_mlx_pixel_put(cub, x + i, y + j, 0x808080);
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
		cofy = y * M_SIZE;
		cofx = 0;
		x = 0;
		while (cub->map_2d[y][x])
		{
			if (x > 0)
				cofx = x * M_SIZE;
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
	cub->p_x *= S_SIZE;
	cub->p_y *= S_SIZE;
	cub->p_x += S_SIZE / 2;
	cub->p_y += S_SIZE / 2;
	set_textures(cub);
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