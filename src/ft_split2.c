#include "../inc/cub.h"

static int	count_word(char const *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while (whitespaces(str[i]))
			i++;
		if (str[i])
		{
			while (str[i] && !whitespaces(str[i]))
				i++;
			cnt += 1;
		}
	}
	return (cnt);
}

static int	word_len(char const *str, int i)
{
	int	cnt;

	cnt = 0;
	while (str[i] && !whitespaces(str[i]))
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static int	splitter(char **str, char const *s, int i)
{
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && whitespaces(s[i]))
			i++;
		if (s[i])
		{
			k = 0;
			str[j] = malloc(word_len(s, i) + 1);
			if (!str[j])
				return (0);
			while (s[i] && !whitespaces(s[i]))
				str[j][k++] = s[i++];
			str[j++][k] = 0;
		}
	}
	str[j] = 0;
	return (1);
}

char	**ft_split2(char const *s)
{
	char	**str;

	if (s == 0)
		return (0);
	str = malloc(sizeof(char *) * (count_word(s) + 1));
	if (!str)
		return (0);
	if (!splitter(str, s, 0))
		return (0);
	return (str);
}