/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongolee <jongolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:00:34 by jongolee          #+#    #+#             */
/*   Updated: 2023/08/08 03:29:00 by jongolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

int	init(t_data *data, pthread_t **threads, char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (!is_input_valid(av[i], 0, 1))
			return (0);
		i++;
	}
	data->id = 0;
	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->eating_time = ft_atoi(av[3]);
	data->sleeping_time = ft_atoi(av[4]);
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	data->eat_counter = 0;
	pthread_mutex_init(&data->mutex, NULL);
	data->state = malloc(sizeof(int) * data->philo_num);
	data->last_eat_start_sec = malloc(sizeof(int) * data->philo_num);
	data->last_eat_start_usec = malloc(sizeof(int) * data->philo_num);
	*threads = malloc(sizeof(pthread_t) * data->philo_num);
	if (!(data->state || data->last_eat_start_sec || data->last_eat_start_usec || *threads))
		on_error(MALLOC);
	return (1);
}

void	*philo(void *arg)
{
	t_data data;

	pthread_mutex_lock(&((t_data *)arg)->mutex);
	((t_data *)arg)->id++;
	data = *(t_data *)arg;
	pthread_mutex_unlock(&((t_data *)arg)->mutex);
	printf("%d\n", data.id);
	return (0);
}

void	make_philos(t_data data, pthread_t *threads)
{
	struct timeval	tv;
	int				i;

	i = 0;
	gettimeofday(&tv, NULL);
	while (i < data.philo_num)
	{
		data.state[i] = THINKING;
		data.last_eat_start_sec[i] = tv.tv_sec;
		data.last_eat_start_usec[i] = tv.tv_usec;
		pthread_create(threads + i, NULL, philo, &data);
		i++;
	}
}

void	join_philos(pthread_t *threads, int philos)
{
	int i;

	i = 0;
	while (i < philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

// void	kill_philos(t_data data)
// {
// 	int				i;
// 	int				over;
// 	struct timeval	tv;
// 	i = 0;
// 	over = 0;
// 	while (i < data.philo_num)
// 	{
// 		gettimeofday(&tv, NULL);
// 		pthread_mutex_lock(&data.mutex);
// 		if ((tv.tv_sec - data.last_eat_start_sec[i]) * 1000 + (tv.tv_usec - data.last_eat_start_usec[i]) / 1000 >= data.time_to_die && (data.state[i] != DEAD || data.state[i] != DONE))
// 		{
// 			data.state[i] = DEAD;
// 			print_died(tv.tv_sec, tv.tv_usec, data.id);
// 			over++;
// 		}
// 		pthread_mutex_unlock(&data.mutex);
// 		i++;
// 		if (over == data.philo_num)
// 			break ;
// 		if (i == data.philo_num)
// 			i = 0;
// 	}
// }


void	free_data(t_data data, pthread_t **threads)
{
	free(data.state);
	free(data.last_eat_start_sec);
	free(data.last_eat_start_usec);
	free(*threads);
}

void	hi()
{
	system("leaks philo");
}

int main(int ac, char **av)
{
	atexit(hi);
	pthread_t		*threads;
	t_data			data;

	if (!(ac == 5 || ac == 6))
		on_error(ARG);
	if (!init(&data, &threads, av))
		return (0);
	make_philos(data, threads);
	monitor_philos(data);
	join_philos(threads, data.philo_num);
	free_data(data, &threads);
	pthread_mutex_destroy(&data.mutex);
	return (0);
}