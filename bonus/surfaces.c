#include "../inc/cub.h"

int	create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	put_sky(t_cub *cub)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	color = create_trgb(cub->rgb_c->r, cub->rgb_c->g, cub->rgb_c->b);
	while (y < (WIN_HEIGTH / 2))
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(cub, x, y , color);
			x += 1;
		}
		y += 1;
	}
	return (y);
}

void	put_surfaces(t_cub *cub)
{
	int x;
	int	color;
	int y = put_sky(cub);
	color = create_trgb(cub->rgb_f->r, cub->rgb_f->g, cub->rgb_f->b);
	while (y < WIN_HEIGTH)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(cub, x, y , color);
			x += 1;
		}
		y += 1;
	}
}