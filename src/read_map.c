/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:44 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/11 16:34:32 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

int ft_free(t_big *all)
{
	free(all->map);
	return(0);
}
int ft_error(char *str)
{
	int i;
	int k;

	i = 0;
	k = ft_strlen2(str);
	write(1, "Error\n", 6);
	write(1, str, k);
	write(1, "\n", 1);
	return (0);
}

int checkline(char *buffer)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (buffer[i])
		{
			if(buffer[i] == '\n')
				size++;
			i++;
		}
	return(size);
}

int read_map(int fd)
{
	char	buffer[11];
	int		size;

	buffer[10] = '\0';
	size = 1;
	if(read(fd, 0, 0) < 0 || fd < 0)
		return (1);
	while(read(fd, buffer, 10) > 0)
		size +=  checkline(buffer);
	close(fd);
	return (size);
}

int main(void)
{
	int size;
	int i;
	int fd;
	int k;
	t_big all;

	i = 0;
	k = 0;
	size = read_map(open("./map.txt",O_RDONLY));
	if (size <= 2)
		return(ft_error("invalid map"));
	all.map = malloc((size + 1) * sizeof(char*));
	if (!all.map)
		return (ft_free(&all));
	all.map[size] = 0;
	fd = open("./map.txt",O_RDONLY);
	while (i < size)
	{
		all.map[i] = get_next_line(fd); // MANQUE FONCTIONNEMENT SI ERROR DE GNL
		i++;
	}
	i = 0;
	while(i < size)
		printf("%s", all.map[i++]);
}
