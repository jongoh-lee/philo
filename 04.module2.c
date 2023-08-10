/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04.module2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:52:47 by jongohlee         #+#    #+#             */
/*   Updated: 2023/08/10 17:04:41 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	fork_up(t_data *data, int id)
{
	pthread_mutex_lock(&data->fork_mutexes[id-1]);
	pthread_mutex_lock(&data->fork_mutexes[id % data->philo_num]);
	if (data->forks[(id-1)] == '1' && data->forks[id % data->philo_num] == '1')
	{
		data->forks[(id-1)] = '0';
		print_log(data, FORK, id);
		data->forks[id % data->philo_num] = '0';
		print_log(data, FORK, id);
	}
}

void	eating(t_data *data, int id)
{
	struct timeval	tv;

	print_log(data, EATING, id);
	gettimeofday(&tv, NULL);
	data->start_eat_time[id-1] = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (++data->eat_count[id-1] == data->eat_end)
	{
		pthread_mutex_lock(&data->full_mutex);
		data->full_philo++;
		if (data->full_philo == data->philo_num)
		{
			pthread_mutex_lock(&data->over_mutex);
			data->is_over = 1;
			pthread_mutex_unlock(&data->over_mutex);
		}
		pthread_mutex_unlock(&data->full_mutex);
	}
}

void	fork_down(t_data *data, int id)
{
	data->forks[(id-1)] = '1';
	data->forks[id % data->philo_num] = '1';
	pthread_mutex_unlock(&data->fork_mutexes[id-1]);
	pthread_mutex_unlock(&data->fork_mutexes[id % data->philo_num]);
}

