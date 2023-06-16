#include "../inc/cub.h"

char	poss_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'W')
		return (WEST);
	if(c == 'E')
		return (EAST);
	if (c == 'D')
		return (DOR);
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
		j = (-1);
		while (map[i][++j])
		{
			if (poss_char(map[i][j]) == 0)
				exit_error(cub);
			if (pos == true && poss_char(map[i][j]) != 1 && poss_char(map[i][j]) != 68)
				exit_error(cub);
			if (poss_char(map[i][j]) != 1 && poss_char(map[i][j]) != 68)
			{
				cub->p_or = poss_char(map[i][j]);
				cub->p_x = j;
				cub->p_y = i;
				pos = true;
			}
		}
	}	
}
int check_sp(char **s,int i ,int j)
{
	if( s[i][j] == ' ')
	{
		if (i && (int)ft_strlen(s[i - 1]) > j
			&& s[i - 1][j] != ' ' && s[i - 1][j] != '1')
			return (-1);
		if (s[i][j + 1] && s[i][j + 1] != ' '
			&& s[i][j + 1] != '1')
			return (-1);
		if (s[i + 1] && (int)ft_strlen(s[i + 1]) > j
			&&  s[i + 1][j] != ' ' && s[i + 1][j] != '1')
			return (-1);
		if (j  && s[i][j - 1] != ' ' && s[i][j - 1] != '1')
			return (-1);

	}
	return (0);
}

void	check_walls2(char **s, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while(s[i][j++] == ' ');
		if (s[i][j - 1] != '1')
				exit_error(cub);
		j = 0;
		while (s[i][j])
		{
			if(i == 0 && s[i][j] != ' ' && s[i][j] != '1')
				exit_error(cub);
			if(check_sp(s, i , j) == -1)
				exit_error(cub);
			if(!s[i + 1]  && s[i][j] != ' ' && s[i][j] != '1')
				exit_error(cub);
			j++;
		}
		while(s[i][--j] == ' ');
		if (s[i][j] != '1')
				exit_error(cub);
		i++;
	}
}
