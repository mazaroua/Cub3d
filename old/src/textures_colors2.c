#include "../inc/cub.h"

char first_elements(char *str)
{
	if (!strcmp("NO", str))
        return ('N');
    if (!strcmp("SO", str))
        return ('S');
    if (!strcmp("WE", str))
        return ('W');
    if (!strcmp("EA", str))
        return ('E');
	if (!strcmp("F", str))
        return ('F');
    if (!strcmp("C", str))
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
		exit_error(cub);
	i = 0;
	f = 0;
	while (s[i])
	{
		if (s[i] == ',')
			f += 1;
		if (s[i + 1])
		{
			if (s[i] == ',' && s[i + 1] == ',')
				exit_error(cub);
		}
		i++;
	}
	if (f != 2)
		exit_error(cub);
}

void	valid_colors(t_cub *cub, char *s, char c)
{
	int		i;
	char	**sp;
	int		code;

	count_comma(s, cub);
	i = 0;
	sp = ft_split(s, ',');
	if (size_map(sp) != 3)
		exit_error(cub);
	i = 0;
	while (sp[i])
	{
		if (!isnot_dig(sp[i]))
			exit_error(cub);
		code = ft_atoi(sp[i]);
		if (!(code >= 0 && code <= 255))
			exit_error(cub);
		ft_color(cub, code, i, c);
		i += 1;
	}
	if (cub->rgb_c->r == cub->rgb_f->r && cub->rgb_c->g == cub->rgb_f->g 
		&& cub->rgb_c->b ==  cub->rgb_f->b)
		exit_error(cub);
	free_2d(sp);
}
