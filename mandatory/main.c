/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-har <isel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:07:54 by isel-har          #+#    #+#             */
/*   Updated: 2023/06/20 17:07:55 by isel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

char	***get_elements(char **map)
{
	int		i;
	char	***pmap;

	pmap = ft_malloc(sizeof(char **) * (size_map(map) + 1));
	i = 0;
	while (i < 6)
	{
		pmap[i] = ft_split2(map[i]);
		i += 1;
	}
	pmap[i] = 0;
	return (pmap);
}

bool	v_extension(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (s[i] == 'b' && s[i - 1] == 'u'
		&& s[i - 2] == 'c' && s[i - 3] == '.')
		return (false);
	return (true);
}

void	pars_cub(t_cub *cub, char *arg)
{
	cub->fd_m = open(arg, O_RDONLY);
	if (cub->fd_m == -1)
	{
		write(2, "Error\n", 6);
		free(cub);
		exit (EXIT_FAILURE);
	}
	cub->map_1d = get_map(cub->fd_m, 0);
	if (cub->map_1d[0] == 0)
		exit_error(cub, 1);
	cub->all = ft_split(cub->map_1d, '\n');
	cub->element = get_elements(cub->all);
	cub->map_2d = cub->all + 6;
	check_elements(cub->element, cub);
	check_map(cub->map_2d, cub, -1);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_error(0, 0);
	if (v_extension(av[1]))
		exit_error(0, 0);
	cub = ft_malloc(sizeof(t_cub));
	pars_cub(cub, av[1]);
	check_walls2(cub->map_2d, cub);
	creation(cub);
	return (0);
}
