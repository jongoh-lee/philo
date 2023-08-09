/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:00:34 by jongolee          #+#    #+#             */
/*   Updated: 2023/08/10 02:44:32 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

int	check_arg(char **av, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!is_input_valid(av[i], 0, 1))
			return (0);
		i++;
	}
	return (1);
}

int	init(t_data *data, pthread_t **threads, char **av, int ac)
{
	if (check_arg(av, ac) == 0)
		return (0);
	data->id = 0;
	data->time_to_die = ft_atoi(av[2]);
	data->eating_time = ft_atoi(av[3]);
	data->sleeping_time = ft_atoi(av[4]);
	data->eat_count = 0;
	if (ac == 6)
		data->eat_end = ft_atoi(av[5]);
	else
		data->eat_end = -1;
	data->philo_num = ft_atoi(av[1]);
	pthread_mutex_init(&data->id_mutex, NULL);
	pthread_mutex_init(&data->fork_mutex, NULL);
	pthread_mutex_init(&data->over_mutex, NULL);
	pthread_mutex_init(&data->full_mutex, NULL);
	data->is_over = 0;
	data->full_philo = 0;
	data->start_eat_time = malloc(sizeof(long long) * data->philo_num);
	data->forks = malloc(sizeof(char) * data->philo_num);
	data->eat_count = malloc(sizeof(int) * data->philo_num);
	*threads = malloc(sizeof(pthread_t) * data->philo_num);
	if (!(data->start_eat_time || data->forks || data->eat_count || *threads))
		on_error(MALLOC);
	return (1);
}

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
		fork_down(data, id);
		usleep(data->eating_time * 1000);
		sleeping(data, id);
		usleep(data->sleeping_time * 1000);
		thinking(data, id);
	}
	return (0);
}

void	make_philos(t_data *data, pthread_t **threads)
{
	struct timeval	tv;
	int				i;

	i = 0;
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_sec * 1000 + tv.tv_usec/1000;
	while (i < data->philo_num)
	{
		data->eat_count[i] = 0;
		data->start_eat_time[i] = data->start_time;
		data->forks[i] = 1;
		pthread_create(*threads + i, NULL, philo, data);
		i++;
	}
}

void	detach_philos(pthread_t **threads, int philos)
{
	int i;

	i = 0;
	while (i < philos)
	{
		pthread_detach((*threads)[i]);
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

void	free_data(t_data *data, pthread_t **threads)
{
	free(data->start_eat_time);
	free(data->forks);
	free(*threads);
}

// void	hi()
// {
// 	system("leaks philo");
// }

int main(int ac, char **av)
{
	// atexit(hi);
	pthread_t		*threads;
	t_data			data;

	if (!(ac == 5 || ac == 6))
		on_error(ARG);
	if (!init(&data, &threads, av, ac))
		return (0);
	make_philos(&data, &threads);
	detach_philos(&threads, data.philo_num);
	monitor_philos(&data);
	free_data(&data, &threads);
	pthread_mutex_destroy(&data.id_mutex);
	pthread_mutex_destroy(&data.fork_mutex);
	pthread_mutex_destroy(&data.over_mutex);
	pthread_mutex_destroy(&data.full_mutex);
	return (0);
}
