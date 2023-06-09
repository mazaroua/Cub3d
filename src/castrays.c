
#include "../inc/cub.h"


void DDA(t_cub *cub)
{	
	t_ray	ray;

	ray.dx = (cub->next_x * SCALE_SIZE) - cub->p_minix;
    ray.dy = (cub->next_y * SCALE_SIZE) - cub->p_miniy;
	if (abs(ray.dx) > abs(ray.dy))
		ray.steps = abs(ray.dx);
	else
		ray.steps = abs(ray.dy);
	ray.Xinc = ray.dx / ray.steps;
    ray.Yinc = ray.dy / ray.steps;
	ray.X = cub->p_minix;
    ray.Y = cub->p_miniy;
    while (ray.steps >= 0)
	{
        my_mlx_pixel_put(cub, round(ray.X)\
		, round(ray.Y), 0xff0000);
        ray.X += ray.Xinc;
        ray.Y += ray.Yinc;
		ray.steps--;
    }
}

double	set_angle(double angle)
{
	if (angle > 2 * M_PI)
		angle -= (2 * M_PI);
	if (angle < 0)
		 angle += (2 * M_PI);
	return (angle);
}

void	cast_all_rays(t_cub *cub)
{  
	int		i;
	double	rayangle;

	rayangle = cub->angle - (FOV_AGL / 2);
	rayangle = set_angle(rayangle);
	i = 0;
	while (i < cub->num_rays)
	{
		intersections(rayangle, cub);
	 	rayangle += FOV_AGL / (double)cub->num_rays;
		rayangle = set_angle(rayangle);
		render_walls(rayangle, cub, i);
     	i += 1;
    }
}