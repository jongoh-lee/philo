/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongolee <jongolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:02:51 by jongolee          #+#    #+#             */
/*   Updated: 2023/07/21 19:18:38 by jongolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	on_error(int ERROR_CODE)
{
	if (ERROR_CODE == MALLOC)
		ft_putendl_fd("Error\nmalloc failed\n", 2);
	else if (ERROR_CODE == INPUT)
		ft_putendl_fd("Error\ninput in valid\n", 2);
	exit(EXIT_FAILURE);
}
