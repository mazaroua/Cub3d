#include "../inc/cub.h"

void    mouse_rotate(t_cub *cub)
{
    if (cub->ROT_TO_RIGHT)
    {
        if (cub->angle >= 355 * (M_PI / 180))
        {
                cub->angle = 0;
                return ;
        }
        cub->angle = cub->angle * (180 / M_PI);
        cub->angle += 2;
        cub->angle = cub->angle * (M_PI / 180);

    }
    else if (cub->ROT_TO_LEFT)
    {
        if (cub->angle <= 0)
        {
            cub->angle = 355 * (M_PI / 180);
            return ;
        }
        cub->angle = cub->angle * (180 / M_PI);
    	cub->angle -= 2;
        cub->angle = cub->angle * (M_PI / 180);

    }
    put_surfaces(cub);
    cast_all_rays(cub);
	zoomed_map(cub, 0, 0);
	put_cursos(cub);
    mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
}

int    mouse(int x, int y, t_cub *cub)
{
    (void)y;
    cub->ROT_TO_RIGHT = 0;
    cub->ROT_TO_LEFT = 0;
    static int    last_x;

    if (x > WIN_WITH / 2)
    {
        if (x < last_x)
        {
            cub->ROT_TO_LEFT = 1;
            last_x = x;
        }
        else if (x > last_x)
        {
            last_x = x;
            cub->ROT_TO_RIGHT = 1;
        }
    }
    else if (x < WIN_WITH / 2)
    {
        if (x > last_x)
        {
            cub->ROT_TO_RIGHT = 1;
            last_x = x;
        }
        else if (x < last_x)
        {
            last_x = x;
            cub->ROT_TO_LEFT = 1;
        }
    }
    mouse_rotate(cub);
    return (0);
}

int	check_wall(t_cub *cub, int x, int y)
{
	int	fpx;
	int	fpy;

	fpx = (int)floor(x) / S_SIZE;
	fpy = (int)floor(y) / S_SIZE;
	if (fpx < 0 || fpx > cub->win_width
		|| fpy < 0 || fpy > cub->win_height)
		return (1);
	if (cub->map_2d[fpy][fpx] == '1')
		return (1);
	if (cub->map_2d[fpy][fpx] == 'D')
		return (2);
	if (cub->map_2d[fpy][fpx] == 'x')
		return (3);
	return (0);
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

void draw_mini_map(t_cub *cub, int y)
{
	int x;
	int cofx;
	int cofy;

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
				put_square(cub, cofx, cofy, 0x4A4F50);
			else if (cub->map_2d[y][x] == 'D')
				put_square(cub, cofx, cofy, 0xFEDF32);
			else
				put_square(cub, cofx, cofy, 0x669A9E);
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
	cub->door_index = 0;
	cub->door_row = 0;
	cub->p_minix = cub->p_x * SCALE_SIZE;
	cub->p_miniy = cub->p_y * SCALE_SIZE;
	set_textures(cub);
	cast_all_rays(cub);
	zoomed_map(cub, 0, 0);
	put_cursos(cub);
}

int	ft_close(t_cub *cub)
{
	release_all(cub, 'f');
	return (0);
}

int	gun_animation(t_cub *cub)
{
	static int i;
	if (cub->gun_key)
	{
		if (i >= 0 && i < 2)
			cub->n_of_img = 0;
		else if (i >= 2 && i < 4)
			cub->n_of_img = 1;
		else if (i >= 4 && i < 6)
			cub->n_of_img = 2;
		else if (i >= 6 && i < 8)
			cub->n_of_img = 3;
		else if (i >= 8 && i < 10)
			cub->n_of_img = 4;
		else if (i >= 10 && i < 12)
			cub->n_of_img = 5;
		else if (i >= 12 && i < 14)
			cub->n_of_img = 6;
		else if (i == 14)
		{
			i = 0;
			cub->n_of_img = 0;
			draw(cub);
			cub->gun_key = 0;
		}
		draw(cub);
		i++;
	}
	return (0);
}

void creation(t_cub *cub)
{
	init_values(cub);
	cub->w_ptr = mlx_new_window(cub->m_ptr, WIN_WITH, WIN_HEIGTH, "cub3d");
	cub->data->img = mlx_new_image(cub->m_ptr, WIN_WITH, WIN_HEIGTH);
	cub->data->addr = mlx_get_data_addr(cub->data->img, &cub->data->bits_per_pixel \
	, &cub->data->line_length, &cub->data->endian);
	put_surfaces(cub);
	put_player(cub);
	mlx_hook(cub->w_ptr, 02, (1L<<0), ft_move, cub);
	mlx_hook(cub->w_ptr, 6, 0,  &mouse, cub);
	mlx_hook(cub->w_ptr, 17, 0, ft_close, cub);
	mlx_loop_hook(cub->m_ptr, gun_animation, cub);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->gun_sprite[0], (WIN_WITH / 2) - (166 / 2), WIN_HEIGTH - 122);
	mlx_loop(cub->m_ptr);
}