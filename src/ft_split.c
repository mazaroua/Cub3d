
#include "../inc/cub.h"

static int	count_word(char const *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			while (str[i] && str[i] != c)
				i++;
			cnt += 1;
		}
	}
	return (cnt);
}

static int	word_len(char const *str, char c, int i)
{
	int	cnt;

	cnt = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static void	ft_free(char **str, int j)
{
	while (j--)
		free(str[j]);
	free(str);
}

static int	splitter(char **str, char const *s, char c, int i)
{
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			k = 0;
			str[j] = malloc(word_len(s, c, i) + 1);
			if (!str[j])
			{
				ft_free(str, j);
				return (0);
			}
			while (s[i] && s[i] != c)
				str[j][k++] = s[i++];
			str[j++][k] = 0;
		}
	}
	str[j] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (s == 0)
		return (0);
	str = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!str)
		return (0);
	if (!splitter(str, s, c, 0))
		return (0);
	return (str);
}
