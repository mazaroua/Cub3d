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

	if (x < 0  || x > WIN_WIDTH || y < 0 || y > WIN_HEIGTH)
		return ;
	dst = c->data->addr + (y * c->data->line_length + x * (c->data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

int	f_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i += 1;
	return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	new = ft_malloc(f_strlen(s1) + f_strlen(s2) + 2);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	free(s2);
	free(s1);
	return (new);
}

int	ft_atoi(char *str)
{
	int	sum;
	int	sign;

	sum = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + *str - '0';
		str++;
	}
	return (sign * sum);
}

bool	isnot_dig(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}