/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongolee <jongolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:00:34 by jongolee          #+#    #+#             */
/*   Updated: 2023/07/21 20:23:03 by jongolee         ###   ########.fr       */
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
	*threads = malloc(sizeof(pthread_t *) * data->philo_num);
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
	while (data.state[data.id] != DEAD)
	{
		if (check_side())
	}
	if (data.eat_counter != data.must_eat)
		printf("dead\n");
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

void	wait_philos(pthread_t *threads, int philos)
{
	int i;

	i = 0;
	while (i < philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	kill_philos(t_data data)
{
	int				i;
	int				dead;
	struct timeval	tv;

	i = 0;
	while (i < data.philo_num)
	{
		gettimeofday(&tv, NULL);
		if ((tv.tv_sec - data.last_eat_start_sec[i]) * 1000 + (tv.tv_usec - data.last_eat_start_usec[i]) / 1000 >= data.time_to_die)
		{
			pthread_mutex_lock(&data.mutex);
			data.state[i] = DEAD;
			pthread_mutex_unlock(&data.mutex);
			dead(i);
		}
		if (data.state[i] == DEAD)
			dead++;
		i++;
		if (dead != PHILOS && i == PHILOS)
		{
			i = 0;
			dead = 0;
		}
		else if (dead == PHILOS)
			break ;
	}
}

int main(int ac, char **av)
{
	pthread_t		*threads;
	t_data			data;

	if (!(ac == 5 || ac == 6))
	{
		perror("1)number_of_philosophers\n\
		2)time_to_die(ms)\n\
		3)time_to_eat(ms)\n\
		4)time_to_sleep(ms)\n\
		5)[number_of_times_each_philosopher_must_eat]\n\
		input please");
		exit(1);
	}
	if (!init(&data, &threads, av))
		return (0);
	make_philos(data, threads);
	kill_philos(data);
	wait_philos(threads, data.philo_num);
	return (0);
}


// 	//2. 생명 or 다 먹었는지 확인하는 스레드 만들기 > 스레드 내부에서 처리 할 경우 cs시간이 오버되어 사망 후 10ms안에 출력을 못할 수 있음
// 	i = 0;
// 	dead_man = 0;
// 	i = 0;
// 	while (i < PHILOS)
// 	{
// 		pthread_join(thread[i], NULL);
// 		i++;
// 	}