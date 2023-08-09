/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:50:17 by jongolee          #+#    #+#             */
/*   Updated: 2023/08/10 02:05:21 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	print_log(t_data *data, int LOG_MSG, int id)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if ((tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_eat_time[id-1] < data->time_to_die)
	{
		if (LOG_MSG == FORK)
			printf("%lldms %d has taken a fork\n", (tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_time, id);
		else if (LOG_MSG == EATING)
			printf("%lldms %d is eating\n", (tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_time, id);
		else if (LOG_MSG == SLEEPING)
			printf("%lldms %d is sleeping\n", (tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_time, id);
		else if (LOG_MSG == THINKING)
			printf("%lldms %d is thinking\n", (tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_time, id);
	}
}
