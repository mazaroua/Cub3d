/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:44:57 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 17:48:03 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

char	first_elements(char *str)
{
	if (!ft_strcmp("NO", str))
		return ('N');
	if (!ft_strcmp("SO", str))
		return ('S');
	if (!ft_strcmp("WE", str))
		return ('W');
	if (!ft_strcmp("EA", str))
		return ('E');
	if (!ft_strcmp("F", str))
		return ('F');
	if (!ft_strcmp("C", str))
		return ('C');
	return (0);
}

void	ft_color(t_cub *cub, int code, int i, char c)
{
	if (c == 'c')
	{
		if (i == 0)
			cub->rgb_c->r = code;
		if (i == 1)
			cub->rgb_c->g = code;
		if (i == 2)
			cub->rgb_c->b = code;
	}
	if (c == 'f')
	{
		if (i == 0)
			cub->rgb_f->r = code;
		if (i == 1)
			cub->rgb_f->g = code;
		if (i == 2)
			cub->rgb_f->b = code;
	}
}

void	count_comma(char *s, t_cub *cub)
{
	int	f;
	int	i;

	if (s[ft_strlen(s) - 1] == ',')
		exit_error(cub, 3);
	i = 0;
	f = 0;
	while (s[i])
	{
		if (s[i] == ',')
			f += 1;
		if (s[i + 1])
		{
			if (s[i] == ',' && s[i + 1] == ',')
				exit_error(cub, 3);
		}
		i++;
	}
	if (f != 2)
		exit_error(cub, 3);
}

void	get_color_code(char **sp, t_cub *cub, char c)
{
	int	i;
	int	code;

	i = 0;
	while (sp[i])
	{
		if (!isnot_dig(sp[i]))
		{
			free_2d(sp);
			exit_error(cub, 3);
		}
		code = ft_atoi(sp[i]);
		if (!(code >= 0 && code <= 255))
		{
			free_2d(sp);
			exit_error(cub, 3);
		}
		ft_color(cub, code, i, c);
		i += 1;
	}
}

void	valid_colors(t_cub *cub, char *s, char c)
{
	char	**sp;

	count_comma(s, cub);
	sp = ft_split(s, ',');
	if (size_map(sp) != 3)
	{
		free_2d(sp);
		exit_error(cub, 3);
	}
	get_color_code(sp, cub, c);
	free_2d(sp);
}
