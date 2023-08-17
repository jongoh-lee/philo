#include "./main.h"

void	ft_sleep(long long time, int last)
{
	while (1)
	{
		if (get_time() - time >= last * 1000)
			break ;
		else
			usleep(1);
	}

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
		usleep((data->eating_time) * 100);
	while (1)
	{
		fork_up(data, id);
		eating(data, id);
		fork_down(data, id);
		print_log(data, SLEEPING, id);
		ft_sleep(get_time(), data->sleeping_time);
		print_log(data, THINKING, id);
	}
	return (0);
}

void	make_philos(t_data *data, pthread_t **threads)
{
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
	data->start_time = get_time();
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
	long long		now;

	while (1)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&data->full_mutex);
			if (data->full_philo == data->philo_num)
			{
				pthread_mutex_lock(&data->over_mutex);
				return ;
			}
			pthread_mutex_unlock(&data->full_mutex);
			pthread_mutex_lock(&data->time_mutex);
			now = get_time();
			if (now - data->start_eat_time[i] >= data->time_to_die * 1000)
			{
				pthread_mutex_lock(&data->over_mutex);
				printf("\033[0;31m%lld %d died\n", (now - data->start_time) / 1000, i + 1);
				return ;
			}
			pthread_mutex_unlock(&data->time_mutex);
			i++;
		}
		usleep(100);
	}
}

void	print_log2(int LOG_MSG, int id, long long now)
{
	if (LOG_MSG == SLEEPING)
		printf("%lld %d is sleeping\n", now, id);
	else if (LOG_MSG == THINKING)
		printf("%lld %d is thinking\n", now, id);
}

void	print_log(t_data *data, int LOG_MSG, int id)
{
	struct timeval	tv;
	long long		now;

	pthread_mutex_lock(&data->time_mutex);
	pthread_mutex_lock(&data->over_mutex);
	gettimeofday(&tv, NULL);
	now = (get_time() - data->start_time) / 1000;
	if (LOG_MSG == FORK)
		printf("%lld %d has taken a fork\n", now, id);
	else if (LOG_MSG == EATING)
		printf("%lld %d is eating\n", now, id);
	else
		print_log2(LOG_MSG, id, now);
	pthread_mutex_unlock(&data->over_mutex);
	pthread_mutex_unlock(&data->time_mutex);
}
