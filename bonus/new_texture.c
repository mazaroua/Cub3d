#include "../inc/cub.h"

void	horiz_cursor(t_cub * cub)
{
	int	i;
	int	j;
	int	ep;

	j = WIN_HEIGTH / 2;
	ep = 0;
	while (ep < 3)
	{
		i = (WIN_WIDTH / 2) - 15;
		while (i < (WIN_WIDTH / 2) + 15)
		{
			my_mlx_pixel_put(cub, i, j + ep, 0xFEDF32);
			i += 1;
		}
		ep += 1;
	}
}

void	put_cursos(t_cub *cub)
{
	int	i;
	int	j;
	int	ep;
	horiz_cursor(cub);
	j = (WIN_HEIGTH / 2) - 15;
	i = WIN_WIDTH / 2;
	while (j < (WIN_HEIGTH / 2) + 15)
	{
		ep = 0;
		while (ep < 3)
		{
			my_mlx_pixel_put(cub, i + ep, j, 0xFEDF32);
			ep += 1;
		}
		j += 1;
	}
}

t_tx   *new_texture(t_cub *cub, char *file)
{
	t_tx	*tx;

	tx = ft_malloc(sizeof(t_tx));
	tx->ptr = mlx_xpm_file_to_image(cub->m_ptr, file, &tx->width, &tx->height);
	if (!tx->ptr)
		return (0);
	tx->data = (unsigned int *)mlx_get_data_addr(tx->ptr, &tx->bpp \
	,&tx->size_line, &tx->endian);
	if (!tx->data)
		return (0);
	return (tx);
}

void	texture_failure(t_tx *t)
{
	if (t->ptr == NULL)
	{
		write(2, IMG_ERR, 18);
		free(t);
		exit (1);
	}
}

void	check_texture(t_cub *cub)
{
	t_tx	*t;

	t = ft_malloc(sizeof(t_tx));
	t->ptr = mlx_xpm_file_to_image(cub->m_ptr, cub->n_texture, &t->width, &t->height);
	texture_failure(t);
	t->ptr = mlx_xpm_file_to_image(cub->m_ptr, cub->w_texture, &t->width, &t->height);
	texture_failure(t);
	t->ptr = mlx_xpm_file_to_image(cub->m_ptr, cub->s_texture, &t->width, &t->height);
	texture_failure(t);
	t->ptr = mlx_xpm_file_to_image(cub->m_ptr, cub->e_texture, &t->width, &t->height);
	texture_failure(t);
	t->ptr = mlx_xpm_file_to_image(cub->m_ptr, "textures/door.xpm", &t->width, &t->height);
	texture_failure(t);
	free(t);
}

void	set_textures(t_cub *cub)
{
	check_texture(cub);
	cub->north_txt = new_texture(cub, cub->n_texture);
	cub->south_txt = new_texture(cub, cub->s_texture);
	cub->west_txt = new_texture(cub, cub->w_texture);
	cub->east_txt = new_texture(cub, cub->e_texture);
	cub->door_txt = new_texture(cub, "textures/door.xpm");
}