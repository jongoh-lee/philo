/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:02 by jongohlee         #+#    #+#             */
/*   Updated: 2023/10/08 18:47:03 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	on_error(int ERROR_CODE)
{
	if (ERROR_CODE == MALLOC)
		printf("Error\nmalloc failed\n");
	else if (ERROR_CODE == INPUT)
		printf("Error\ninput in valid\n");
	else if (ERROR_CODE == ARG)
	{
		printf(
			"[argument format] 1 2 3 4 [5]\n"
			"1)number_of_philosophers\n"
			"2)time_to_die(ms)\n"
			"3)time_to_eat(ms)\n"
			"4)time_to_sleep(ms)\n"
			"[5]number_of_times_each_philosopher_must_eat\n");
	}
	exit(EXIT_FAILURE);
}
