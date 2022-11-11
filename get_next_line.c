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



#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int	main(void)
{
	int	fd;
	// char	*s = "fabio Valli Vieira";
	char	c;
	char 	c1;
	int	i = 0;

	fd = open("test.txt", O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	// fd = open("test.txt", O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1)
	{
		printf("open() failed\n");
		return (1);
	}
	printf("fd = %d\n", fd);
	// write(fd, s, strlen(s));
	// while(read(fd, &c, 1) && i < 6)
	while(read(fd, &c, 1))
	{
		if(c == '\r')
			break ;
		printf("%c", c);
		i++;
	}
	// read(fd, &c, 1);
	// read(fd, &c1, 1);
	// printf("c=%c\n", c);
	// printf("c1=%c\n", c1);
	if (close(fd) == -1)
	{
		printf("close() failed\n");
		return (1);
	}
	return (0);
}
