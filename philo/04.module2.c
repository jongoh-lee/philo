/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04.module2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:52:47 by jongohlee         #+#    #+#             */
/*   Updated: 2023/08/12 14:40:42 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	fork_up(t_data *data, int id)
{
	pthread_mutex_lock(&data->fork_mutexes[id - 1]);
	pthread_mutex_lock(&data->fork_mutexes[id % data->philo_num]);
	if (data->forks[(id - 1)] == '1' && \
	data->forks[id % data->philo_num] == '1')
	{
		data->forks[(id - 1)] = '0';
		print_log(data, FORK, id);
		data->forks[id % data->philo_num] = '0';
		print_log(data, FORK, id);
	}
}

void	eating(t_data *data, int id)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->start_eat_time[id - 1] = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	print_log(data, EATING, id);
	usleep(data->eating_time * 1000);
}

void	fork_down(t_data *data, int id)
{
	if (++data->eat_count[id - 1] == data->eat_end)
	{
		pthread_mutex_lock(&data->full_mutex);
		data->full_philo++;
		pthread_mutex_unlock(&data->full_mutex);
	}
	data->forks[(id - 1)] = '1';
	data->forks[id % data->philo_num] = '1';
	pthread_mutex_unlock(&data->fork_mutexes[id - 1]);
	pthread_mutex_unlock(&data->fork_mutexes[id % data->philo_num]);
}
