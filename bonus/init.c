#include "../inc/cub.h"

void get_angle(t_cub *cub)
{
	if (cub->p_or == NORTH)
		cub->angle = 270 * (M_PI / 180);
	if (cub->p_or == SOUTH)
		cub->angle = 90 * (M_PI / 180);
	if (cub->p_or == EAST)
		cub->angle = 0;
	if (cub->p_or == WEST)
		cub->angle = 180 * (M_PI / 180);
}

void    init_values(t_cub *cub)
{
    int tmp;

    cub->y_map = 0;
	cub->x_map = 0;
	cub->door_index = 0;
	cub->door_row = 0;
	cub->all_map = 0;
	cub->data = ft_malloc(sizeof(t_data));
	while (cub->map_2d[cub->y_map])
	{
		cub->x_map = 0;
   		tmp = 0;
		while (cub->map_2d[cub->y_map][cub->x_map])
			cub->x_map += 1;
		if (cub->x_map > tmp)
			tmp = cub->x_map;
		cub->y_map += 1;
	}
	cub->x_map = tmp;
    cub->win_width = cub->x_map * S_SIZE;
    cub->win_height = cub->y_map * S_SIZE;
    get_angle(cub);
    cub->m_ptr = mlx_init();
	//
	cub->n_of_img = 0;
	cub->gun_key = 0;
	cub->gun_sprite = ft_malloc(sizeof(void *) * 7);
	cub->gun_sprite[0] = mlx_xpm_file_to_image(cub->m_ptr, "textures/1.xpm", &cub->w, &cub->h);
	cub->gun_sprite[1] = mlx_xpm_file_to_image(cub->m_ptr, "textures/2.xpm", &cub->w, &cub->h);
	cub->gun_sprite[2] = mlx_xpm_file_to_image(cub->m_ptr, "textures/3.xpm", &cub->w, &cub->h);
	cub->gun_sprite[3] = mlx_xpm_file_to_image(cub->m_ptr, "textures/4.xpm", &cub->w, &cub->h);
	cub->gun_sprite[4] = mlx_xpm_file_to_image(cub->m_ptr, "textures/5.xpm", &cub->w, &cub->h);
	cub->gun_sprite[5] = mlx_xpm_file_to_image(cub->m_ptr, "textures/6.xpm", &cub->w, &cub->h);
	cub->gun_sprite[6] = mlx_xpm_file_to_image(cub->m_ptr, "textures/7.xpm", &cub->w, &cub->h);
}