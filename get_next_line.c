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

#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#define BUFFER_SIZE 4
int main()
{
int fd, sz;
char *c = (char *) malloc((BUFFER_SIZE + 1) *sizeof(char));

fd = open("foo.txt", O_RDONLY | O_CREAT);
if (fd < 0) { perror("r1"); exit(1); }
sz = read(fd, c, 1);
// c = get_next_line(fd);
printf("Those bytes are as follows: % s\n", c);
}
char	*get_next_line(int fd)
{
	size_t	buffer;
	size_t	i;
	size_t	len;
	char	*c;

	buffer = BUFFER_SIZE;
	i = 0;
	len = read(fd, (void *)&c[i], 1);
	i++;
	while (c[i] != '\r')
	{
		// ft_read_buffer
		printf("%s", c[i]);
		len = read(fd, (void *)&c[i], 1);
		i++;
	}
	return (c);
}
size_t	ft_size_line_buffer(int fd, size_t buffer)
{
	size_t	i;
	char	*c;

	i = 0;
	while (i < buffer)
	{
		read(fd, (void *)&c[i], 1);
git push --set-upstream origin master
	return (i);
}
// char	*ft_read_buffer(int fd, size_t buffer)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < buffer)
// 	{
// 		if ()
// 	}
// }

