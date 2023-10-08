/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04.module2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:46:35 by jongohlee         #+#    #+#             */
/*   Updated: 2023/10/08 18:46:50 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	return (now);
}

void	fork_up(t_data *data, int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&data->fork_mutexes[id - 1]);
		pthread_mutex_lock(&data->fork_mutexes[id % data->philo_num]);
		data->forks[(id - 1)] = '0';
		print_log(data, FORK, id);
		data->forks[id % data->philo_num] = '0';
		print_log(data, FORK, id);
	}
	else
	{
		pthread_mutex_lock(&data->fork_mutexes[id % data->philo_num]);
		pthread_mutex_lock(&data->fork_mutexes[id - 1]);
		data->forks[id % data->philo_num] = '0';
		print_log(data, FORK, id);
		data->forks[(id - 1)] = '0';
		print_log(data, FORK, id);
	}
}

void	eating(t_data *data, int id)
{
	pthread_mutex_lock(&data->time_mutex);
	data->start_eat_time[id - 1] = get_time();
	pthread_mutex_unlock(&data->time_mutex);
	print_log(data, EATING, id);
	ft_sleep(get_time(), data->eating_time);
}

void	fork_down(t_data *data, int id)
{
	if (++data->eat_count[id - 1] == data->eat_end)
	{
		pthread_mutex_lock(&data->full_mutex);
		data->full_philo++;
		pthread_mutex_unlock(&data->full_mutex);
	}
	if (id % 2 == 0)
	{
		data->forks[(id - 1)] = '1';
		data->forks[id % data->philo_num] = '1';
		pthread_mutex_unlock(&data->fork_mutexes[id - 1]);
		pthread_mutex_unlock(&data->fork_mutexes[id % data->philo_num]);
	}
	else
	{
		data->forks[id % data->philo_num] = '1';
		data->forks[(id - 1)] = '1';
		pthread_mutex_unlock(&data->fork_mutexes[id % data->philo_num]);
		pthread_mutex_unlock(&data->fork_mutexes[id - 1]);
	}
}
