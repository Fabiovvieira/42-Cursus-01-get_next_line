/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:48:45 by marvin            #+#    #+#             */
/*   Updated: 2022/11/08 21:48:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*(p++) = 0;
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = (void *)malloc(nmemb * size);
	if (p == NULL)
		return (p);
	ft_bzero(p, nmemb * size);
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*sub;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if ((size_t)start >= size)
		return (ft_strdup(""));
	if (size - 1 - start < len)
		len = size - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, (s + start), len + 1);
	return (sub);
}

char *get_line(char** str, ssize_t	len_read)
{
	char	*str1;
	char	*tmp;
	int	i;

	i = 0;
	tmp = ft_strdup(*str);
	if ((ft_strchr(*str, '\n')))
	{
		str1 = ft_strdup(*str);
		while ((*str)[i] != '\n' && (*str)[i])
			i++;
		str1[i + 1] = '\0';
		*str = ft_substr(tmp, i + 1, ft_strlen(tmp) - i + 1);
	}
	else if (len_read == 0 && (*str)[0] != '\0')
	{
		str1 = ft_strdup(*str);
		while ((*str)[i] != '\0')
			i++;
		str1[i] = '\0';
		*str = ft_substr(tmp, i + 1, ft_strlen(tmp) - i + 1);
	}
	else
		str1 = NULL;
	free (tmp);
	return (str1);
}

static char *ft_read_line(char *str, char *buffer, ssize_t len_read)
{
	char	*tmp;

	buffer[len_read] = '\0';
	if (str == NULL)
	{
		tmp = ft_strdup(buffer);
		free(str);
	}
	else
	{
		tmp = ft_strjoin(str, buffer);
		free(str);
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	ssize_t	len_read = BUFFER_SIZE;
	static char	*str;
	char	*str1;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	buffer = ft_calloc(sizeof(char),(BUFFER_SIZE + 1));
	while (!(ft_strchr(buffer, '\n')) && len_read != 0)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		str = ft_read_line(str,buffer, len_read);
	}
	str1 = get_line(&str,len_read);
	free(buffer);
	return (str1);
}
/*int main()
{
	int fd;
	char	*str;
	ssize_t	len_read = BUFFER_SIZE;
	int	i;

	i = 1;
	fd = open("foo.txt", O_RDONLY | O_CREAT);
	if (fd < 0) { perror("r1"); exit(1); }
	printf("BUFFER SIZE is:%lu\n", len_read);
	while ((str = get_next_line(fd)))
	{
			printf("LINE - %3d || lengh - %3lu: %s",i++,ft_strlen(str), str);
	}
	free(str);
	return (0);
}*/