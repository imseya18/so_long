/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:09:35 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/11 16:21:54 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clear_buff(int behavior, char *buffer)
{
	int	i;

	i = 0;
	if (behavior == 0)
	{
		while (i < BUFFER_SIZE + 1)
			buffer[i++] = '\0';
	}
	if (behavior == 1)
		free(buffer);
	return (0);
}

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	strfill(char *str, char *s1, char *s2)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s1[i])
		str[k++] = s1[i++];
	free(s1);
	i = 0;
	while (s2[i])
		str[k++] = s2[i++];
	free(s2);
	str[k] = '\0';
}

char	*strjoin(char *s1, char *s2)
{
	char	*str;

	if ((s1 == 0) && s2)
		return (s2);
	if ((s2 == 0) && s1)
		return (s1);
	if (s1 == 0 || s2 == 0)
		return (0);
	str = malloc((ft_strlen2(s1) + ft_strlen2(s2) + 1) * sizeof(char));
	if (!str)
	{	
		free(s1);
		free (s2);
		return (0);
	}
	strfill(str, s1, s2);
	return (str);
}
