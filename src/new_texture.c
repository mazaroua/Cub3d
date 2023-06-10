#include "../inc/cub.h"

t_tx   *new_texture(t_cub *cub, char *file)
{
	t_tx	*tx;

	tx = ft_malloc(sizeof(t_tx));
	tx->ptr = mlx_xpm_file_to_image(cub->m_ptr, file, &tx->width, &tx->height);
	if (!tx->ptr)
	{
		write(2, IMG_ERR, 18);
		exit (1);
	}
	tx->data = (unsigned int *)mlx_get_data_addr(tx->ptr, &tx->bpp \
	,&tx->size_line, &tx->endian);
	if (!tx->data)
		return (0);
	return (tx);
}

void	set_textures(t_cub *cub)
{
	cub->north_txt = new_texture(cub, cub->n_texture);
	cub->south_txt = new_texture(cub, cub->s_texture);
	cub->west_txt = new_texture(cub, cub->w_texture);
	cub->east_txt = new_texture(cub, cub->e_texture);
	cub->door_txt = new_texture(cub, "textures/door.xpm");
}