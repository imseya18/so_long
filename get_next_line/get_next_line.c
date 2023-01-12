/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:09:32 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/11 16:34:04 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_buffer_sort(char *buffer)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i] != '\0')
		buffer[k++] = buffer[i++];
	buffer[k] = '\0';
	return (buffer);
}

char	*ft_read(char *buffer, int *error)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	if (ft_strlen2(buffer) == 0)
		return (0);
	while (buffer[i] != '\n' && buffer[i] != '\0')
			i++;
	if (buffer[i] == '\n')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
	{
		*error = -1;
		return (ft_clear_buff (0, buffer));
	}
	while (k < i)
	{
		str[k] = buffer[k];
		k++;
	}
	str[k] = '\0';
	return (str);
}

char	*check_line(char *str, int fd, char *buffer, int error)
{
	int	check;

	check = BUFFER_SIZE;
	while (check == BUFFER_SIZE)
	{
		if ((str && str[ft_strlen2(str) - 1] == '\n'))
		{
			ft_buffer_sort(buffer);
			return (str);
		}
		ft_clear_buff(0, buffer);
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
			return (ft_clear_buff(0, buffer));
		str = strjoin(str, ft_read(buffer, &error));
		if (error == -1 || !str)
			return (ft_clear_buff(1, str));
	}
	ft_buffer_sort(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	int			error;

	error = 0;
	if (read(fd, 0, 0) < 0)
		return (ft_clear_buff(0, buffer));
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	str = ft_read(buffer, &error);
	if (error == -1)
		return (0);
	str = check_line(str, fd, buffer, error);
	return (str);
}
