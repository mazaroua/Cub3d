#include "../inc/cub.h"

char	*get_map(int fd)
{
	char	*r_map;
	char	*line;
	int		i;

	r_map = ft_malloc(1);
	*r_map = 0;
	i = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i > 6 && line[0] == '\n')
			exit_error(0);
		if (line[0] != '\n')
		{
			i += 1;
			r_map = ft_strjoin2(r_map, line);
		}
		else
			free(line);
	}
	if (i < 6)
		exit_error(0);
	return (r_map);
}

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
		free(cub);
		exit_error(0);
	}
	cub->map_1d = get_map(cub->fd_m);
	if (cub->map_1d[0] == 0)
		exit_error(cub);
	cub->all = ft_split(cub->map_1d, '\n');
	cub->element = get_elements(cub->all);
	cub->map_2d = cub->all + 6;
	check_elements(cub->element, cub);
	check_map(cub->map_2d, cub, -1);
}

void	f()
{
	system("leaks cub3d");
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_error(0);
	if (v_extension(av[1]))
		exit_error(0);
	cub = ft_malloc(sizeof(t_cub));
	pars_cub(cub, av[1]);
	creation(cub);
	release_all(cub, 'x');
}