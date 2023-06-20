#include "../inc/cub.h"

void    mouse_rotate(t_cub *cub)
{
    if (cub->ROT_TO_RIGHT)
    {
		printf("right: %f\n", cub->angle * (180 / M_PI));
        if (cub->angle >= 355 * (M_PI / 180))
        {
                cub->angle = 0;
                return ;
        }
        cub->angle = cub->angle * (180 / M_PI);
        cub->angle += 5;
        cub->angle = cub->angle * (M_PI / 180);

    }
    else if (cub->ROT_TO_LEFT)
    {
		printf("left: %f\n", cub->angle * (180 / M_PI));
        if (cub->angle <= 0)
        {
			printf("Negative: %f\n", cub->angle * (180 / M_PI));
            cub->angle = 355 * (M_PI / 180);
            return ;
        }
        cub->angle = cub->angle * (180 / M_PI);
    	cub->angle -= 5;
        cub->angle = cub->angle * (M_PI / 180);

    }
    draw(cub);
}

int    mouse(int x, int y, t_cub *cub)
{
	mlx_mouse_hide();
    (void)y;
	cub->ROT_TO_RIGHT = 0;
    cub->ROT_TO_LEFT = 0;
	if (x == WIN_WIDTH / 2)
		return (0);
    if (x > WIN_WIDTH / 2)
    {
		cub->ROT_TO_RIGHT = 1;
		mlx_mouse_move(cub->w_ptr, WIN_WIDTH / 2, WIN_HEIGTH / 2);
    }
    else if (x < WIN_WIDTH / 2)
    {
		cub->ROT_TO_LEFT = 1;
		mlx_mouse_move(cub->w_ptr, WIN_WIDTH / 2, WIN_HEIGTH / 2);
    }
    mouse_rotate(cub);
    cub->ROT_TO_RIGHT = 0;
    cub->ROT_TO_LEFT = 0;
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
	exit(0);
	return (0);
}

int	gun_animation(t_cub *cub)
{
	static int i;

	if (i >= 0 && i < 1)
		cub->n_of_img = 0;
	else if (i >= 1 && i < 2)
		cub->n_of_img = 1;
	else if (i >= 2 && i < 3)
		cub->n_of_img = 2;
	else if (i >= 3 && i < 4)
		cub->n_of_img = 3;
	else if (i >= 4 && i < 5)
		cub->n_of_img = 4;
	else if (i >= 5 && i < 6)
		cub->n_of_img = 5;
	else if (i >= 6 && i < 7)
		cub->n_of_img = 6;
	else if (i == 7)
	{
		i = 0;
		cub->gun_key = 0;
	}
	draw(cub);
	i++;
	return (0);
}

int	gun_key(int key, int x, int y, t_cub *cub)
{
	(void)x, (void)y;
	if (key == 1)
	{
		cub->gun_key = 1;
	}
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
	if (cub->gun_key == 1)
		gun_animation(cub);
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
	mlx_hook(cub->w_ptr, 6, 0,  &mouse, cub);
	mlx_hook(cub->w_ptr, 17, 0, ft_close, cub);
	mlx_mouse_hook(cub->w_ptr, gun_key, cub);
	mlx_loop_hook(cub->m_ptr, keys, cub);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->data->img, 0, 0);
	mlx_put_image_to_window(cub->m_ptr, cub->w_ptr, cub->gun_sprite[0],\
	(WIN_WIDTH / 2) - (166 / 2), WIN_HEIGTH - 122);
	mlx_loop(cub->m_ptr);
}