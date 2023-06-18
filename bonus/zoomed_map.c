#include "../inc/cub.h"

void zoomed_map(t_cub *cub, double x, double y)
{
	double start_x;
	double start_y;
	start_y = cub->p_y - 200;
	start_x = cub->p_x - 200;
	while (y < 300)
	{
		x = 0;
		while (x < 250)
		{
			int calc_x = (start_x + x) / 32;
			int calc_y = (start_y + y) / 32;
			if (calc_x < 0 || calc_y < 0 || calc_x >= cub->x_map
				|| calc_y >= cub->y_map)
				my_mlx_pixel_put(cub, x, y, 0x2cb3d8);
			else if (cub->map_2d[calc_y][calc_x] == '1')
				my_mlx_pixel_put(cub, x, y, 0x4A4F50);
			else if (cub->map_2d[calc_y][calc_x] == 'D')
				my_mlx_pixel_put(cub, x, y, 0xFEDF32);
			else
				my_mlx_pixel_put(cub, x, y, 0x2cb3d8);
			x += 1;
		}
		y += 1;
	}
	mini_player(cub,  200, 200, 10);
}
