/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:09:23 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/26 17:17:32 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_fill_tab_f(t_listpf *start, char *tab)
{	
	int		i;
	int		j;
	char	*temp;

	j = 0;
	while (start->next != NULL)
	{
		i = 0;
		temp = start->content;
		while (i < start->size)
			tab[j++] = temp[i++];
		start = start->next;
	}
	temp = start->content;
	i = 0;
	while (i < start->size)
		tab[j++] = temp[i++];
	tab[j] = '\0';
}

char	*ft_tab(t_listpf *start, int size)
{
	char	*tab;

	tab = malloc((size + 1 * sizeof(char)));
	if (!tab)
		return (0);
	ft_fill_tab_f(start, tab);
	return (tab);
}

int	ft_pars(char ftm, t_listpf **start, va_list arg, int *error)
{	
	int	size;

	size = 0;
	if (ftm == 'c')
		size = ft_char(va_arg(arg, int), start, error);
	else if (ftm == 's')
		size = ft_string(va_arg(arg, char *), start, error);
	else if (ftm == 'p')
		size = ft_p(va_arg(arg, void *), start, error);
	else if (ftm == 'd')
		size = ft_di(va_arg(arg, int), start, error);
	else if (ftm == 'i')
		size = ft_di(va_arg(arg, int), start, error);
	else if (ftm == 'u')
		size = ft_u(va_arg(arg, unsigned int), start, error);
	else if (ftm == 'x')
		size = ft_x(va_arg(arg, unsigned int), start, error);
	else if (ftm == 'X')
		size = ft_x_maj(va_arg(arg, unsigned int), start, error);
	else if (ftm == '%')
		size = ft_char(ftm, start, error);
	return (size);
}

int	ft_test(const char *ftm, t_listpf **start, va_list arg, int *error)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (ftm[i] && *error == 0)
	{
		if (ftm[i] == '%')
		{
			size = size + ft_pars(ftm[i + 1], start, arg, error);
			i++;
		}
		else
			size = size + ft_char(ftm[i], start, error);
		i++;
	}
	return (size);
}

char	*ft_printf(const char *fmt, ...)
{
	t_listpf	*start;
	va_list		arg;
	int			size;
	int			error;
	char		*check;

	error = 0;
	start = 0;
	if (fmt[0] == '\0')
		return (0);
	va_start(arg, fmt);
	size = ft_test(fmt, &start, arg, &error);
	if (error == 1)
		return (0);
	check = ft_tab(start, size);
	va_end(arg);
	ft_lstclear_pf(&start);
	return (check);
}
