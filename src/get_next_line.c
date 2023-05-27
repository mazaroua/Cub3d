
#include "../inc/get_next_line.h"

char	*find_line(char *src)
{
	int		i;
	char	*dst;

	if (!*src)
		return (NULL);
	dst = malloc(sizeof(char) * len(src) + 2);
	if (!dst)
		return (0);
	i = 0;
	while (src[i])
	{
		if (src[i] == '\n')
		{
			dst[i] = src[i];
			i += 1;
			break ;
		}
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	check_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*skip_old(char *tmp)
{
	int		i;
	int		i2;
	char	*next;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (NULL);
	}
	next = malloc((ft_strlen(tmp) - i) + 1);
	if (!next)
		return (NULL);
	i += 1;
	i2 = 0;
	while (tmp[i])
		next[i2++] = tmp[i++];
	next[i2] = '\0';
	free(tmp);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*nline;
	char		*buf;
	int			rb;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	rb = 1;
	while (!(check_line(tmp)) && rb > 0)
	{
		rb = read(fd, buf, BUFFER_SIZE);
		if (rb == -1)
			return (free(buf), NULL);
		buf[rb] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	nline = find_line(tmp);
	tmp = skip_old(tmp);
	return (free(buf), nline);
}
