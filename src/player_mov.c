#include "../inc/cub.h"

void	player_newpos(t_cub *cub, int key)
{
	if (key == MOVE_FORWARD)
	{
		cub->p_x += 5 * cos(cub->angle);
		cub->p_y += 5 * sin(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
	if (key == MOVE_BACKWARD)
	{
		cub->p_x -= 5 * cos(cub->angle);
		cub->p_y -= 5 * sin(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
	if (key == MOVE_LEFT)
	{
		cub->p_x += 5 * sin(cub->angle);
		cub->p_y -= 5 * cos(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
	if (key == MOVE_RIGHT)
	{
		cub->p_x -= 5 * sin(cub->angle);
		cub->p_y += 5 * cos(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
}

void move_player(t_cub *cub, int keycode)
{
	int	xtmp;
	int	ytmp;

	xtmp = cub->p_x;
	ytmp = cub->p_y;
	player_newpos(cub, keycode);
	if (check_wall(cub, cub->p_x, cub->p_y))
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
	}
}

void	increment_angle(t_cub *cub, int keycode)
{
	if (keycode == RIGHT_ROTATION)
	{
		if (cub->angle >= 355 * (M_PI / 180))
		{
			cub->angle = 0;
			return ;
		}
		cub->angle = cub->angle * (180 / M_PI);
		cub->angle += 5;
		cub->angle = cub->angle * (M_PI / 180);
	}
	if (keycode == LEFT_ROTATION)
	{
		if (cub->angle <= 0)
		{
			cub->angle = 355 * (M_PI / 180);
			return ;
		}
		cub->angle = cub->angle * (180 / M_PI);
			cub->angle -= 5;
		cub->angle = cub->angle * (M_PI / 180);
	}
}

int ft_move(int keycode, t_cub *cub)
{
	fprintf(stderr, "%d\n", keycode);
	if (cub->door == true && keycode == OPEN_DOOR)
	 		cub->map_2d[cub->door_y][cub->door_x] = '0';
	if (keycode == MOVE_FORWARD)
		move_player(cub, keycode);
	if (keycode == MOVE_BACKWARD)
		move_player(cub, keycode);
	if (keycode == MOVE_LEFT)
		move_player(cub, keycode);
	if (keycode == MOVE_RIGHT)
		move_player(cub, keycode);
	if (keycode == RIGHT_ROTATION)
		increment_angle(cub, keycode);
	if (keycode == LEFT_ROTATION)
		increment_angle(cub, keycode);
	if (keycode == ESC)
		exit (0);
	put_surfaces(cub);
	cast_all_rays(cub);
	draw_mini_map(cub);
	if (!check_wall(cub, cub->p_minix, cub->p_miniy))
		my_mlx_pixel_put(cub, cub->p_minix, cub->p_miniy, 0xff00000);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
	return (0);
}