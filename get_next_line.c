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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*p;
	unsigned char	*s;
	size_t			len;

	len = nmemb * size;
	p = (void *)malloc(nmemb * size);
	if (p == NULL)
		return (p);
	s = p;
	while (len--)
		*(s++) = 0;
	return (p);
}

char	*get_line(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(*(str + i)))
		return (NULL);
	while (*(str + i) && *(str + i) != '\n')
		i++;
	tmp = ft_calloc(sizeof(char), (i + 2));
	i = 0;
	while (*(str + i) && *(str + i) != '\n')
	{
		*(tmp + i) = *(str + i);
		i++;
	}
	*(tmp + i) = *(str + i);
	return (tmp);
}

char	*save_rest(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(str + i) && *(str + i) != '\n')
		i++;
	if (!(*(str + i)))
	{
		free (str);
		return (NULL);
	}
	tmp = ft_calloc(sizeof(char), (ft_strlen(str) - i));
	i++;
	while (*(str + i))
		*(tmp + (j++)) = *(str + (i++));
	free (str);
	return (tmp);
}

char	*ft_read_line(char *str, char *buffer, ssize_t len_read)
{
	char	*tmp;

	buffer[len_read] = '\0';
	if (str == NULL)
	{
		tmp = ft_strdup(buffer);
		free(str);
		return (tmp);
	}
	else
	{
		tmp = ft_strjoin(str, buffer);
		free(str);
		return (tmp);
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		len_read;
	static char	*str;
	char		*line;

	len_read = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	while (!(ft_strchr(buffer, '\n')) && len_read != 0)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		if (len_read == -1)
		{
			free (buffer);
			free (str);
			str = NULL;
			return (NULL);
		}
		str = ft_read_line(str, buffer, len_read);
	}
	free(buffer);
	line = get_line(str);
	str = save_rest(str);
	return (line);
}
/*int main()
{
	int fd;
	char	*str;
	ssize_t	len_read = BUFFER_SIZE;
	int	i;

	i = 1;
	fd = open("foo1.txt", O_RDONLY | O_CREAT);
	if (fd < 0) { perror("r1"); exit(1); }
	printf("BUFFER SIZE is:%lu\n", len_read);
	while ((str = get_next_line(fd)))
		printf("LINE - %3d || lengh - %3lu: %s",i++,ft_strlen(str), str);
	free(str);
	return (0);
}*/