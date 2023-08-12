/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.module1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:50:17 by jongolee          #+#    #+#             */
/*   Updated: 2023/08/12 18:15:17 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	*philo(void *arg)
{
	int				id;
	t_data			*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->id_mutex);
	id = ++data->id;
	pthread_mutex_unlock(&data->id_mutex);
	if (id % 2 == 0)
		usleep((data->eating_time) * 200);
	while (1)
	{
		fork_up(data, id);
		eating(data, id);
		fork_down(data, id);
		print_log(data, SLEEPING, id);
		usleep(data->sleeping_time * 1000);
		print_log(data, THINKING, id);
	}
	return (0);
}

void	make_philos(t_data *data, pthread_t **threads)
{
	struct timeval	tv;
	int				i;

	i = 0;
	while (i < data->philo_num)
	{
		data->eat_count[i] = 0;
		data->forks[i] = '1';
		if (pthread_mutex_init(&data->fork_mutexes[i], NULL) < 0)
			return ;
		i++;
	}
	i = 0;
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (i < data->philo_num)
	{
		data->start_eat_time[i] = data->start_time;
		if (pthread_create(*threads + i, NULL, philo, data) != 0)
			return ;
		i++;
	}
}

void	monitor_philos(t_data *data, int i)
{
	struct timeval	tv;
	long long		now;

	while (1)
	{
		usleep(50);
		i = 0;
		while (i < data->philo_num)
		{
			gettimeofday(&tv, NULL);
			now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
			pthread_mutex_lock(&data->full_mutex);
			if (data->full_philo == data->philo_num)
			{
				pthread_mutex_lock(&data->over_mutex);
				return ;
			}
			pthread_mutex_unlock(&data->full_mutex);
			if (now - data->start_eat_time[i] >= data->time_to_die)
			{
				pthread_mutex_lock(&data->over_mutex);
				printf("%lld %d died\n", (now - data->start_time), i + 1);
				return ;
			}
			i++;
		}
	}
}

void	print_log2(t_data *data, int LOG_MSG, int id, long long now)
{
	if (LOG_MSG == SLEEPING)
	{
		pthread_mutex_lock(&data->over_mutex);
		printf("%lld %d is sleeping\n", now, id);
		pthread_mutex_unlock(&data->over_mutex);
	}
	else if (LOG_MSG == THINKING)
	{
		pthread_mutex_lock(&data->over_mutex);
		printf("%lld %d is thinking\n", now, id);
		pthread_mutex_unlock(&data->over_mutex);
	}
}

void	print_log(t_data *data, int LOG_MSG, int id)
{
	struct timeval	tv;
	long long		now;

	gettimeofday(&tv, NULL);
	now = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - data->start_time;
	if (LOG_MSG == FORK)
	{
		pthread_mutex_lock(&data->over_mutex);
		printf("%lld %d has taken a fork\n", now, id);
		pthread_mutex_unlock(&data->over_mutex);
	}
	else if (LOG_MSG == EATING)
	{
		pthread_mutex_lock(&data->over_mutex);
		printf("%lld %d is eating\n", now, id);
		pthread_mutex_unlock(&data->over_mutex);
	}
	else
		print_log2(data, LOG_MSG, id, now);
}
