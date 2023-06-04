#include "../inc/cub.h"

void	player_newpos(t_cub *cub, int key)
{
	if (key == MOVE_FORWARD)
	{
		cub->p_x += 5 * cos(cub->angle);
		cub->p_y += 5 * sin(cub->angle);
	}
	if (key == MOVE_BACKWARD)
	{
		cub->p_x -= 5 * cos(cub->angle);
		cub->p_y -= 5 * sin(cub->angle);
	}
	if (key == MOVE_LEFT)
	{
		cub->p_x += 5 * sin(cub->angle);
		cub->p_y -= 5 * cos(cub->angle);
	}
	if (key == MOVE_RIGHT)
	{
		cub->p_x -= 5 * sin(cub->angle);
		cub->p_y += 5 * cos(cub->angle);
	}
}

void move_player(t_cub *cub, int keycode)
{
	int	xtmp;
	int	ytmp;

	xtmp = cub->p_x;
	ytmp = cub->p_y;
	player_newpos(cub, keycode);
	if (check_wall(cub))
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
	}
	else
		my_mlx_pixel_put(cub, xtmp, ytmp, 0x00000);
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
		exit(0);
	draw_mini_map(cub);
	// intersections(cub);
	// DDA(cub, cub->p_x, cub->p_y, cub->next_x, cub->next_y);
	cast_all_rays(cub);
	my_mlx_pixel_put(cub, cub->p_x, cub->p_y, 0xff0000);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
	return (0);
}