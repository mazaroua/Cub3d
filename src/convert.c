#include "../inc/cub.h"


unsigned int	get_color_in_texture(t_cub *cub, int Y, double wall_height)
{
	int				x;
	int				y;
	unsigned int	color;
	y = Y + (wall_height / 2) - (cub->win_height / 2);
	x = (cub->x_offset / 32) * cub->texture_width;
	y = y * (cub->texture_height / wall_height);
	color = cub->texture_addr[abs((y * cub->texture_height) + x)];
	return (color);
}

void	put_rect(int x, t_cub *cub, double plan_height)
{
	int				top_pixel;
	int 			bottom_pixel;
	unsigned int	color;

	top_pixel = (cub->win_height / 2) - ((int)plan_height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	bottom_pixel = (cub->win_height / 2) + ((int)plan_height / 2);
	if (bottom_pixel > cub->win_height)
		bottom_pixel = cub->win_height;
	while (top_pixel < bottom_pixel)
	{
		color = get_color_in_texture(cub, top_pixel, plan_height);
		my_mlx_pixel_put(cub, x , top_pixel, color);
		top_pixel++;
	}
}

void	render_walls(double rayangle, t_cub *cub, int i)
{
	double	plan_dist;
	double	raydistance;
	double	proj_plan_h;
	double	newang;

	newang = cub->angle - rayangle;
	newang = set_angle(newang);
	raydistance = cal_distance(cub->p_x, cub->p_y, cub->next_x, cub->next_y)\
	* cos(newang);
	if (round(raydistance) == 0)
		raydistance = 1;
	plan_dist = (cub->win_width / 2) / tan(FOV_AGL / 2);
	proj_plan_h = (S_SIZE  / raydistance) * plan_dist;
	put_rect(i, cub, proj_plan_h);
}