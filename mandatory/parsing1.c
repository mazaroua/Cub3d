/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:07:18 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 17:35:16 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

char	*get_map(int fd, int i)
{
	char	*r_map;
	char	*line;

	r_map = ft_malloc(1);
	*r_map = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i > 6 && line[0] == '\n')
		{
			free(line);
			exit_error(0, 0);
		}
		if (line[0] != '\n')
		{
			i += 1;
			r_map = ft_strjoin2(r_map, line);
		}
		else
			free(line);
	}
	return (r_map);
}

int	check_sp(char **s, int i, int j)
{
	if (s[i][j] == ' ')
	{
		if (i && (int)ft_strlen(s[i - 1]) > j
			&& s[i - 1][j] != ' ' && s[i - 1][j] != '1')
			return (-1);
		if (s[i][j + 1] && s[i][j + 1] != ' '
			&& s[i][j + 1] != '1')
			return (-1);
		if (s[i + 1] && (int)ft_strlen(s[i + 1]) > j
			&& s[i + 1][j] != ' ' && s[i + 1][j] != '1')
			return (-1);
		if (j && s[i][j - 1] != ' ' && s[i][j - 1] != '1')
			return (-1);
	}
	return (0);
}

void	skip_spaces(char *s, int *j, char f)
{
	if (f == 'f')
	{
		while (s[*j] == ' ' && s[*j])
			*j += 1;
	}
	else
	{
		*j -= 1;
		while (s[*j] == ' ')
			*j -= 1;
	}
}

void	check_walls2(char **s, t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = 0;
		skip_spaces(s[i], &j, 'f');
		if (s[i][j] != '1')
			exit_error(cub, 3);
		j = 0;
		while (s[i][j])
		{
			if (i == 0 && s[i][j] != ' ' && s[i][j] != '1')
				exit_error(cub, 3);
			if (check_sp(s, i, j) == -1)
				exit_error(cub, 0);
			if (!s[i + 1] && s[i][j] != ' ' && s[i][j] != '1')
				exit_error(cub, 3);
			j++;
		}
		skip_spaces(s[i], &j, 'b');
		if (s[i][j] != '1')
			exit_error(cub, 3);
	}
}
