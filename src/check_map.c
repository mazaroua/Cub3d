#include "../inc/cub.h"

char	poss_char(char c)
{
	if (c == '0' || c == '1' || whitespaces(c))
		return (1);
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'W')
		return (WEST);
	if(c == 'E')
		return (EAST);
	return (0);
}

void	check_map(char **map, t_cub *cub, int i)
{
	int		j;
	bool	pos;

	pos = false;
	if (!*map)
		exit_error(cub);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (poss_char(map[i][j]) == 0)
				exit_error(cub);
			if (pos == true && poss_char(map[i][j]) > 1)
				exit_error(cub);
			if (poss_char(map[i][j]) > 1)
			{
				cub->p_or = poss_char(map[i][j]);
				cub->p_x = j;
				cub->p_y = i;
				pos = true;
			}
		}
	}	
}
/*
void	check_walls(char **s, t_cub *cub)
{
	int		x;
	int		y;
	char	**ds;

	if (s[0][0] != '1')
		exit_error(cub);
	if (s[0][1] == '1')
	{
		x = 1;
		y = 0;
	}
	else
	{
		if (s[1][1])
		{
			x = 1;
			y = 1;
		}
	}
	ds = dup_map(s);
	printf("%d\n", map_path(y, x, ds));
}*/
