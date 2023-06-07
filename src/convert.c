#include "../inc/cub.h"

void	put_rect(int x, t_cub *cub, double plan_height)
{
	int	top_pixel;
	int bottom_pixel;

	top_pixel = (cub->win_height / 2) - ((int)plan_height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	bottom_pixel = (cub->win_height / 2) + ((int)plan_height / 2);
	if (bottom_pixel > cub->win_height)
		bottom_pixel = cub->win_height;
	while (top_pixel < bottom_pixel)
	{
		my_mlx_pixel_put(cub, x , top_pixel, 0xffffff);
		top_pixel++;
	}
}

void	render_walls(t_cub *cub, int i)
{
	double	plan_dist;
	double	raydistance;
	double	proj_plan_h;
	int		j;

	raydistance = cal_distance(cub->p_x, cub->p_y, cub->next_x, cub->next_y);
	plan_dist = (cub->win_width / 2) /  tan(FOV_AGL / 2);
	proj_plan_h = (S_SIZE  / raydistance) * plan_dist;
	put_rect(i, cub, proj_plan_h);
}