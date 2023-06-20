
#include "../inc/cub.h"

void	*ft_malloc(int size)
{
    void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, MEM_ERR, 24);
		exit (2);
	}
	return (ptr);
}

void    exit_error(t_cub *cub, char step)
{
    write(2, "Error\n", 6);
	if (step == 0)
		exit (EXIT_FAILURE);
	if (step > 1)
		free_2d(cub->all);
	free_3d(cub->element);
	if (step >= 3)
	{
		free(cub->c_color);
		free(cub->f_color);
		free(cub->rgb_c);
		free(cub->rgb_f);
		free(cub->n_texture);
		free(cub->s_texture);
		free(cub->e_texture);
		free(cub->w_texture);
	}
	free(cub->map_1d);
	free(cub);
	exit (EXIT_FAILURE);
}

void	release_all(t_cub *cub, char f)
{
	free(cub->map_1d);
	free_3d(cub->element);
	free_2d(cub->all);
	free(cub->e_texture);
	free(cub->n_texture);
	free(cub->w_texture);
	free(cub->s_texture);
	free(cub->f_color);
	free(cub->c_color);
	free(cub->rgb_c);
	free(cub->rgb_f);
	free(cub->data);
	if (f == 'f')
	{
		free(cub->south_txt);
		free(cub->north_txt);
		free(cub->west_txt);
		free(cub->east_txt);
	}
	free(cub);
	exit (0);
}

void	free_3d(char ***s)
{
	int	i;

    if (!**s)
        return ;
	i = 0;
	while (s[i])
		i++;
	i -= 1;
	while (i)
		free_2d(s[i--]);
	free_2d(s[i]);
	free(s);
}

void	free_2d(char **str)
{
	int	i;

    if (!*str)
        return ;
	i = 0;
	while (str[i])
		i += 1;
	while (i)
		free(str[i--]);
	free(str[i]);
	free(str);
}
