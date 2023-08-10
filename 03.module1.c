/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.module1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:50:17 by jongolee          #+#    #+#             */
/*   Updated: 2023/08/10 17:05:48 by jongohlee        ###   ########.fr       */
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
		usleep((data->eating_time) * 900);
	while (1)
	{
		fork_up(data, id);
		eating(data, id);
		usleep(data->eating_time * 1000);
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
		pthread_mutex_init(&data->fork_mutexes[i], NULL);
		i++;
	}
	i = 0;
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_sec * 1000 + tv.tv_usec/1000;
	while (i < data->philo_num)
	{
		data->start_eat_time[i] = data->start_time;
		pthread_create(*threads + i, NULL, philo, data);
		i++;
	}
}

void	monitor_philos(t_data *data)
{
	struct timeval	tv;
	long long		now;
	int				i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->over_mutex);
		if (data->is_over == 1)
			break ;
		pthread_mutex_unlock(&data->over_mutex);
		gettimeofday(&tv, NULL);
		now = tv.tv_sec * 1000 + tv.tv_usec/1000;
		if (now - data->start_eat_time[i] >= data->time_to_die)
		{
			pthread_mutex_lock(&data->over_mutex);
			data->is_over = 1;
			printf("%lldms %d died\n", (now - data->start_time), i + 1);
			pthread_mutex_unlock(&data->over_mutex);
			break ;
		}
		i++;
		if (i == data->philo_num)
			i = 0;
	}
}

void	print_log(t_data *data, int LOG_MSG, int id)
{
	struct timeval	tv;

	pthread_mutex_lock(&data->over_mutex);
	gettimeofday(&tv, NULL);
	if (!data->is_over)
	{
		if (LOG_MSG == FORK)
			printf("%lld %d has taken a fork\n", (tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_time, id);
		else if (LOG_MSG == EATING)
			printf("%lld %d is eating\n", (tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_time, id);
		else if (LOG_MSG == SLEEPING)
			printf("%lld %d is sleeping\n", (tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_time, id);
		else if (LOG_MSG == THINKING)
			printf("%lld %d is thinking\n", (tv.tv_sec * 1000 + tv.tv_usec/1000) - data->start_time, id);
	}
	pthread_mutex_unlock(&data->over_mutex);
}
