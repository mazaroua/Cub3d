#include "../inc/cub.h"

void	still_open(t_cub *cub)
{
	int	i;
	int	j;
	j = 0;
	while (cub->map_2d[j])
	{
		i = 0;
		while (cub->map_2d[j][i])
		{
		 	if (j != cub->door_row && i != cub->door_index
				&& cub->map_2d[j][i] == 'x')
				cub->map_2d[j][i] = 'D';
			i += 1;
		}
		j += 1;
	}
}

void	mini_player(t_cub *cub, int x, int y, int size)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			my_mlx_pixel_put(cub, x + i, y + j, 0xff00000);
			i += 1;
		}
		j += 1;
	}
	if (size == 3)
	{
 		cub->mini_nxtx = (cub->p_x + cos(cub->angle) * 20) * SCALE_SIZE;
		cub->mini_nxty = (cub->p_y + sin(cub->angle) * 20) * SCALE_SIZE;
 		DDA(cub);
	}
}

void	player_newpos(t_cub *cub, int key)
{
	if (key == MOVE_FORWARD)
	{
		cub->p_x += 3 * cos(cub->angle);
		cub->p_y += 3 * sin(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
	if (key == MOVE_BACKWARD)
	{
		cub->p_x -= 3 * cos(cub->angle);
		cub->p_y -= 3 * sin(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
	if (key == MOVE_LEFT)
	{
		cub->p_x += 3 * sin(cub->angle);
		cub->p_y -= 3 * cos(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
	if (key == MOVE_RIGHT)
	{
		cub->p_x -= 3 * sin(cub->angle);
		cub->p_y += 3 * cos(cub->angle);
		cub->p_minix = cub->p_x * SCALE_SIZE;
		cub->p_miniy = cub->p_y * SCALE_SIZE;
	}
}

bool	check_sides(t_cub *cub, int xtmp, int ytmp)
{
	double	right_angle;
	double	left_angle;

	right_angle = set_angle(cub->angle - M_PI / 2);
	intersections(right_angle, cub);
	if (cal_distance(cub->p_x, cub->p_y, cub->next_x , cub->next_y) < 2)
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
		return (true);
	}
	left_angle = set_angle(cub->angle + M_PI / 2);
	intersections(left_angle, cub);
	if (cal_distance(cub->p_x, cub->p_y, cub->next_x , cub->next_y) < 2)
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
		return (true);
	}
	return (false);
}

void move_player(t_cub *cub, int keycode)
{
	int		xtmp;
	int		ytmp;

	xtmp = cub->p_x;
	ytmp = cub->p_y;
	player_newpos(cub, keycode);
	if (check_sides(cub, xtmp, ytmp) == true)
		return;
	intersections(cub->angle, cub);
	if (cal_distance(cub->p_x, cub->p_y, cub->next_x , cub->next_y) < 2)
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
		return ;
	}
	if (check_wall(cub, cub->p_x, cub->p_y) == 1
		|| check_wall(cub, cub->p_x, cub->p_y) == 2)
	{
		cub->p_x = xtmp;
		cub->p_y = ytmp;
	}
}

void	beside_wall(t_cub *cub, int keycode)
{
	if (cub->d_p_dist >= 0 &&  cub->d_p_dist < 6 && cub->door
		&& keycode == OPEN_DOOR)
	{
		cub->door_index = (int)floor(cub->door_x) / S_SIZE;
		cub->door_row = (int)floor(cub->door_y) / S_SIZE;
		if (check_wall(cub, cub->door_x, cub->door_y - S_SIZE) == 2)
			cub->door_row -= 1;
		if (check_wall(cub, cub->door_x - S_SIZE, cub->door_y) == 2)
			cub->door_index -= 1;
		cub->map_2d[cub->door_row][cub->door_index] = 'x';
	}
	if (cub->map_2d[cub->door_row][cub->door_index] == 'x'
		&& cal_distance(cub->p_x, cub->p_y, cub->door_x, cub->door_y) > 46)
		cub->map_2d[cub->door_row][cub->door_index] = 'D';
	still_open(cub);
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

void	draw(t_cub *cub)
{
	put_surfaces(cub);
	cast_all_rays(cub);
	put_cursos(cub);
	if (cub->all_map)
	{
		draw_mini_map(cub, 0);
		mini_player(cub, cub->p_minix, cub->p_miniy, 3);
	}
	else
		zoomed_map(cub, 0, 0);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->gun_sprite[cub->n_of_img],\
	(WIN_WIDTH / 2) - (166 / 2), WIN_HEIGTH - 122);
}

void	movement(int keycode, t_cub *cub)
{
	cub->all_map = 0;
	if (keycode == MOVE_FORWARD)
		cub->move_forward = 1;
	if (keycode == MOVE_BACKWARD)
		cub->move_backward = 1;
	if (keycode == MOVE_LEFT)
		cub->move_left = 1;
	if (keycode == MOVE_RIGHT)
		cub->move_right = 1;
	if (keycode == RIGHT_ROTATION)
		cub->rotation_right = 1;
	if (keycode == LEFT_ROTATION)
		cub->rotation_left = 1;
	if (keycode == ESC)
		exit(0);
	if (keycode == CTRL)
		cub->all_map = 1;
}

int ft_move(int keycode, t_cub *cub)
{
	beside_wall(cub, keycode);
	movement(keycode, cub);
	// if (keycode == CTRL)
	// {

	// 	draw_mini_map(cub, 0);
	// 	mini_player(cub, cub->p_minix, cub->p_miniy, 3);
	// }
	// else
	// 	zoomed_map(cub, 0, 0);
	return (0);
}
