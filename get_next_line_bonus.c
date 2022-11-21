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

#include "get_next_line_bonus.h"

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
	int	i;

	i = 0;
	if ((ft_strchr(*str, '\n')))
	{
		str1 = ft_strdup(*str);
		while ((*str)[i] != '\n' && (*str)[i])
			i++;
		str1[i + 1] = '\0';
		*str = ft_substr(*str, i + 1, ft_strlen(*str) - i + 1);
	}
	else if (len_read == 0 && (*str)[0] != '\0')
	{
		str1 = ft_strdup(*str);
		while ((*str)[i] != '\0')
			i++;
		str1[i + 1] = '\0';
		*str = ft_substr(*str, i + 1, ft_strlen(*str) - i + 1);
	}
	else
		str1 = NULL;
	return (str1);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	ssize_t	len_read = BUFFER_SIZE;
	static char	*str[MAX_FILES_OPENED];
	char	*str1;

	buffer = calloc(sizeof(char),BUFFER_SIZE + 1);
	len_read = read(fd, buffer, BUFFER_SIZE);
	buffer[len_read] = '\0';
	str[fd] = ft_strjoin(str[fd], buffer);
	while (!(ft_strchr(str[fd], '\n')) && len_read != 0)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		buffer[len_read] = '\0';
		str[fd] = ft_strjoin(str[fd], buffer);
	}
	str1 = get_line(&(str[fd]),len_read);
	free(buffer);
	return (str1);
}

int main()
{
	int fd,fd1,fd2;
	char	*str,*str1,*str2;
	int	i;

	fd = open("foo.txt", O_RDONLY | O_CREAT);
	if (fd < 0) { perror("r1"); exit(1); }
	fd1 = open("foo1.txt", O_RDONLY | O_CREAT);
	if (fd1 < 0) { perror("r1"); exit(1); }
	fd2 = open("foo2.txt", O_RDONLY | O_CREAT);
	if (fd2 < 0) { perror("r1"); exit(1); }
	i = 0;
	while ((str = get_next_line(fd)))
	{
		printf("fd - %3d || LINE - %3d || lengh - %3d: %s",fd,i++,ft_strlen(str), str);
	}
	i = 0;
	while ((str1 = get_next_line(fd1)))
	{
		printf("fd - %3d || LINE - %3d || lengh - %3d: %s",fd1,i++,ft_strlen(str1), str1);
	}
	i = 0;
	while ((str2 = get_next_line(fd2)))
	{
		printf("fd - %3d || LINE - %3d || lengh - %3d: %s",fd2,i++,ft_strlen(str2), str2);
	}

	// while ((str2 = get_next_line(fd2)) && (str1 = get_next_line(fd1)) && (str = get_next_line(fd)))
	// {
	// 	printf("fd - %3d || LINE - %3d || lengh - %3d: %s",fd,i++,ft_strlen(str), str);
	// 	printf("fd - %3d || LINE - %3d || lengh - %3d: %s",fd1,i++,ft_strlen(str1), str1);
	// 	printf("fd - %3d || LINE - %3d || lengh - %3d: %s",fd2,i++,ft_strlen(str2), str2);
	// }


	return (0);
}
