#include "../inc/cub.h"

void DDA(t_cub *cub)//should complete this
{
	t_ray	ray;

	ray.dx = cub->next_x - cub->p_x;
    ray.dy = cub->next_y - cub->p_y;
	if (abs(ray.dx) > abs(ray.dy))
		ray.steps = abs(ray.dx);
	else
		ray.steps = abs(ray.dy);
	ray.Xinc = ray.dx / (float)ray.steps;
    ray.Yinc = ray.dy / (float)ray.steps;
	ray.X = cub->p_x;
    ray.Y = cub->p_y;
    while (ray.steps >= 0)
	{
        my_mlx_pixel_put(cub, round(ray.X)\
		, round(ray.Y), 0xff0000);
        ray.X += ray.Xinc;
        ray.Y += ray.Yinc;
		ray.steps--;
    }
}

void	cast_all_rays(t_cub *cub)
{  
	int		i;
	double	rayangle;

	rayangle = cub->angle - (FOV_AGL / 2);
	i = 0;
	while (i < cub->num_rays)
	{
		intersections(rayangle, cub);
		DDA(cub);
	 	rayangle += FOV_AGL / cub->num_rays;

     	i += 1;
		// printf("width = %d\n", cub->win_width);
		// printf("i = %d\n", i);
    }
}