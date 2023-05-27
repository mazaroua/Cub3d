#include "../inc/cub.h"

void draw_vector(t_cub *cub)
{
	cub->next_x = cub->p_x + cos(cub->angle) * 50;
	cub->next_y = cub->p_y + sin(cub->angle) * 50;

	mlx_pixel_put(cub->m_ptr, cub->w_ptr, cub->next_x, cub->next_y, 0xff0000);
}

void put_square(t_cub *cub, int x, int y)
{
	int i;
	int j;

	j = 0;
	while (j < 32)
	{
		i = 0;
		while (i < 32)
		{
			mlx_pixel_put(cub->m_ptr, cub->w_ptr, x + i, y + j, 0xfffffff);
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
				put_square(cub, cofx, cofy);
			x += 1;
		}
		y += 1;
	}
}

void orient_player(t_cub *cub, int color)
{
	/*int	j;
	int	i;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;*/
	mlx_pixel_put(cub->m_ptr, cub->w_ptr, cub->p_x, cub->p_y, color);
	/*
	while (true)
	{
		if (tmp == 32)
			break ;
		mlx_pixel_put(cub->m_ptr, cub->w_ptr, cub->p_x + i, cub->p_y + j, color);
		if (cub->p_or == NORTH)
			j -= 1;
		if (cub->p_or == WEST)
			i -= 1;
		if (cub->p_or == SOUTH)
			j += 1;
		if (cub->p_or == EAST)
			i += 1;
		tmp += 1;
	}*/
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

void move_player(t_cub *cub, char o)
{
	int	xtmp;
	int	ytmp;

	xtmp = cub->p_x;
	ytmp = cub->p_y;
	if (o == 'u')
		cub->p_y -= 1;
	if (o == 'd')
		cub->p_y += 1;
	if (o == 'l')
		cub->p_x -= 1;
	if (o == 'r')
		cub->p_x += 1;
	if (check_wall(cub))
	{
		printf("dkhl \n");
		cub->p_x = xtmp;
		cub->p_y = ytmp;
	}
	else
		mlx_pixel_put(cub->m_ptr, cub->w_ptr, xtmp, ytmp, 0x00000);
}

int ft_move(int keycode, t_cub *cub)
{
	if (keycode == 13)
		move_player(cub, 'u');
	if (keycode == 1)
		move_player(cub, 'd');
	if (keycode == 0)
		move_player(cub, 'l');
	if (keycode == 2)
		move_player(cub, 'r');
	if (keycode == 124)
	{
		cub->angle += 0.0872665;
	}
	if (keycode == 123)
	{
		cub->angle -= 0.0872665;
	}
	mlx_clear_window(cub->m_ptr, cub->w_ptr);
	draw_mini_map(cub);
	orient_player(cub, 0xff0000);
	draw_vector(cub);
	return (0);
}

void put_player(t_cub *cub)
{
	cub->p_x *= 32;
	cub->p_y *= 32;
	cub->p_x += 32 / 2;
	cub->p_y += 32 / 2;
	orient_player(cub, 0xff0000);
	draw_vector(cub);
	mlx_hook(cub->w_ptr, 02, (1L << 0), ft_move, cub);
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

void creation(t_cub *cub)
{
	cub->angle = 0.00;
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
	get_angle(cub);
	draw_mini_map(cub);
	put_player(cub);
	mlx_loop(cub->m_ptr);
}