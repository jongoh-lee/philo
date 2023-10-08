#include "./main_bonus.h"

long long get_time()
{
	struct timeval tv;
	long long now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	return (now);
}

void	sema_waiter(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->philo_num)
		sem_wait(data->sem_eat_end);
}

void	fork_up(t_data *data)
{
	sem_wait(data->sem_forks);
	sem_wait(data->sem_forks);
	print_log(data, FORK);
	print_log(data, FORK);
}

void	eating(t_data *data)
{
	data->eat_start_time = get_time();
	print_log(data, EATING);
	ft_usleep(get_time(), data->eating_time);
}

void	fork_down(t_data *data)
{
	if (++data->eat_count == data->max_eat_num)
		sem_post(data->sem_eat_end);
	sem_post(data->sem_forks);
	sem_post(data->sem_forks);
}
