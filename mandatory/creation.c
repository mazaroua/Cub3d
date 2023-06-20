#include "../inc/cub.h"

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
	return (0);
}

void put_player(t_cub *cub)
{
	cub->p_x *= S_SIZE ;
	cub->p_y *= S_SIZE;
	cub->p_x += S_SIZE / 2;
	cub->p_y += S_SIZE / 2;
	cub->door_index = 0;
	cub->door_row = 0;
	set_textures(cub);
	cast_all_rays(cub);
}

int	ft_close(t_cub *cub)
{
	release_all(cub, 'f');
	return (0);
}


int	key_up(int keycode, t_cub *cub)
{
	if (keycode == MOVE_FORWARD)
		cub->move_forward = 0;
	if (keycode == MOVE_BACKWARD)
		cub->move_backward = 0;
	if (keycode == MOVE_LEFT)
		cub->move_left = 0;
	if (keycode == MOVE_RIGHT)
		cub->move_right = 0;
	if (keycode == RIGHT_ROTATION)
		cub->rotation_right = 0;
	if (keycode == LEFT_ROTATION)
		cub->rotation_left = 0;
	return (0);
}

int	keys(t_cub *cub)
{
	if (cub->move_forward == 1)
		move_player(cub, MOVE_FORWARD);
	if (cub->move_backward == 1)
		move_player(cub, MOVE_BACKWARD);
	if (cub->move_right == 1)
		move_player(cub, MOVE_RIGHT);
	if (cub->move_left == 1)
		move_player(cub, MOVE_LEFT);
	if (cub->rotation_right == 1)
		increment_angle(cub, RIGHT_ROTATION);
	if (cub->rotation_left == 1)
		increment_angle(cub, LEFT_ROTATION);
	draw(cub);
	return (0);
}

void	init_keys(t_cub *cub)
{
	cub->move_backward = 0;
	cub->move_forward = 0;
	cub->move_right = 0;
	cub->move_left = 0;
	cub->rotation_right = 0;
	cub->rotation_left = 0;
	cub->gun_key = 0;
}

void creation(t_cub *cub)
{
	init_values(cub);
	init_keys(cub);
	cub->w_ptr = mlx_new_window(cub->m_ptr, WIN_WIDTH, WIN_HEIGTH, "cub3d");
	cub->data->img = mlx_new_image(cub->m_ptr, WIN_WIDTH, WIN_HEIGTH);
	cub->data->addr = mlx_get_data_addr(cub->data->img, &cub->data->bits_per_pixel \
	, &cub->data->line_length, &cub->data->endian);
	put_surfaces(cub);
	put_player(cub);
	mlx_hook(cub->w_ptr, 2, 0, ft_move, cub);
	mlx_hook(cub->w_ptr, 3, 0, key_up, cub);
	mlx_hook(cub->w_ptr, 17, 0, ft_close, cub);
	mlx_loop_hook(cub->m_ptr, keys, cub);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
	mlx_loop(cub->m_ptr);
}