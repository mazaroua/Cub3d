/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:36:49 by mazaroua          #+#    #+#             */
/*   Updated: 2023/06/21 00:37:44 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

char	*ft_strdup(char *s)
{
	char	*new;
	int		i;

	new = ft_malloc(ft_strlen(s) + 1);
	i = -1;
	while (s[++i])
		new[i] = s[i];
	new[i] = 0;
	return (new);
}

void	my_mlx_pixel_put(t_cub *c, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGTH)
		return ;
	dst = c->data->addr + \
	(y * c->data->line_length + x * (c->data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	size_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

int	whitespaces(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}
