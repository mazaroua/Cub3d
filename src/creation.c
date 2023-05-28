#include "../inc/cub.h"

void DDA(t_cub *cub)
{
	int	i;
	int	dx;
	int dy;
	int	steps;
	float	Xinc;
	float	Yinc;
	float 	X;
	float	Y;

	dx = cub->next_x - cub->p_x;
    dy = cub->next_y - cub->p_y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	Xinc = dx / (float)steps;
    Yinc = dy / (float)steps;
	X = cub->p_x;
    Y = cub->p_y;
    while (steps >= 0)
	{
        mlx_pixel_put(cub->m_ptr, cub->w_ptr, round(X), round(Y), 0xff0000);
        X += Xinc;
        Y += Yinc;
		steps--;
    }
}

void draw_vector(t_cub *cub)
{
	cub->next_x = cub->p_x + cos(cub->angle) * 100;
	cub->next_y = cub->p_y + sin(cub->angle) * 100;

	mlx_pixel_put(cub->m_ptr, cub->w_ptr, cub->next_x, cub->next_y, 0xff0000);
	DDA(cub);
}

void put_square(t_cub *cub, int x, int y, int color)
{
	int i;
	int j;

	j = 0;
	while (j < 32)
	{
		i = 0;
		while (i < 32)
		{
			mlx_pixel_put(cub->m_ptr, cub->w_ptr, x + i, y + j, color);
			if (!(i % 32) || !(j % 32))
				mlx_pixel_put(cub->m_ptr, cub->w_ptr, x + i, y + j, 0x808080);
			i += 1;
		}
		j += 1;
	}
}

void draw_mini_map(t_cub *cub)
{
	int x;
	int y;
	int cofx;
	int cofy;

	y = 0;
	while (cub->map_2d[y])
	{
		x = 0;
		cofy = y * 32;
		cofx = 0;
		x = 0;
		while (cub->map_2d[y][x])
		{
			if (x > 0)
				cofx = x * 32;
			if (cub->map_2d[y][x] == '1')
				put_square(cub, cofx, cofy, 0xffffff);
			if (cub->map_2d[y][x] != '1')
				put_square(cub, cofx, cofy, 0x000000);
			x += 1;
		}
		y += 1;
	}
}

bool	check_wall(t_cub *cub)
{
	int	fpx;
	int	fpy;

	fpx = (cub->p_x) / 32;
	fpy = (cub->p_y) / 32;
	if (cub->map_2d[fpy][fpx] == '1')
		return (true);
	return (false);
}

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
	}}

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
		mlx_pixel_put(cub->m_ptr, cub->w_ptr, xtmp, ytmp, 0x00000);
}

void	increment_angle(t_cub *cub, int keycode)
{
	if (keycode == RIGHT_ROTATION)
	{
		if (cub->angle >= 360 * (M_PI / 180))
			cub->angle = 0;
		cub->angle += 0.0872665;
	}
	if (keycode == LEFT_ROTATION)
	{
		if (cub->angle <= 0)
			cub->angle = 360 * (M_PI / 180);
		cub->angle -= 0.0872665;
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
	if (keycode == 53)
		exit(0);
	mlx_clear_window(cub->m_ptr, cub->w_ptr);
	draw_mini_map(cub);
	mlx_pixel_put(cub->m_ptr, cub->w_ptr, cub->p_x, cub->p_y, 0xff0000);
	draw_vector(cub);
	return (0);
}

void put_player(t_cub *cub)
{
	cub->p_x *= 32;
	cub->p_y *= 32;
	cub->p_x += 32 / 2;
	cub->p_y += 32 / 2;
	mlx_pixel_put(cub->m_ptr, cub->w_ptr, cub->p_x, cub->p_y, 0xff0000);
}

void get_angle(t_cub *cub)
{
	if (cub->p_or == NORTH)
		cub->angle = 270 * (M_PI / 180);
	if (cub->p_or == SOUTH)
		cub->angle = 90 * (M_PI / 180);
	if (cub->p_or == EAST)
		cub->angle = 0, 00;
	if (cub->p_or == WEST)
		cub->angle = 180 * (M_PI / 180);
}

void	drawing(t_cub *cub)
{
	get_angle(cub);
	draw_mini_map(cub);
	put_player(cub);
	draw_vector(cub);
	mlx_hook(cub->w_ptr, 02, (1L << 0), ft_move, cub);
}

void creation(t_cub *cub)
{
	cub->y_map = 0;
	cub->x_map = 0;
	int tmp = 0;
	while (cub->map_2d[cub->y_map])
	{
		cub->x_map = 0;
		while (cub->map_2d[cub->y_map][cub->x_map])
			cub->x_map += 1;
		if (cub->x_map > tmp)
			tmp = cub->x_map;
		cub->y_map += 1;
	}
	cub->x_map = tmp;
	cub->m_ptr = mlx_init();
	cub->w_ptr = mlx_new_window(cub->m_ptr, cub->x_map * 32, cub->y_map * 40, "cub3d");
	drawing(cub);
	mlx_loop(cub->m_ptr);
}