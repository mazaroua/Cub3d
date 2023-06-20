/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:12:10 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 17:12:13 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	get_colors(t_cub *cub)
{
	cub->rgb_c = ft_malloc(sizeof(t_color));
	cub->rgb_f = ft_malloc(sizeof(t_color));
	valid_colors(cub, cub->c_color, 'c');
	valid_colors(cub, cub->f_color, 'f');
}

void	get_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(cub->element[i][0], "NO"))
			cub->n_texture = ft_strdup(cub->element[i][1]);
		if (!ft_strcmp(cub->element[i][0], "SO"))
			cub->s_texture = ft_strdup(cub->element[i][1]);
		if (!ft_strcmp(cub->element[i][0], "WE"))
			cub->w_texture = ft_strdup(cub->element[i][1]);
		if (!ft_strcmp(cub->element[i][0], "EA"))
			cub->e_texture = ft_strdup(cub->element[i][1]);
		if (!ft_strcmp(cub->element[i][0], "F"))
			cub->f_color = ft_strdup(cub->element[i][1]);
		if (!ft_strcmp(cub->element[i][0], "C"))
			cub->c_color = ft_strdup(cub->element[i][1]);
		i++;
	}
	get_colors(cub);
}

void	duplicated(char *elements, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (elements[i])
	{
		j = i + 1;
		while (elements[j])
		{
			if (elements[j] == elements[i])
			{
				free(elements);
				exit_error(cub, 2);
			}
			j += 1;
		}
		i += 1;
	}
	free(elements);
	get_textures(cub);
}

void	check_elements(char ***map, t_cub *cub)
{
	int		i;
	char	*elements;

	i = 0;
	elements = ft_malloc(7);
	while (i < 6)
	{
		if (first_elements(map[i][0]) == 0
			|| size_map(map[i]) != 2)
		{
			free(elements);
			exit_error(cub, 2);
		}
		else
			elements[i] = first_elements(map[i][0]);
		i += 1;
	}
	elements[i] = 0;
	duplicated(elements, cub);
}
