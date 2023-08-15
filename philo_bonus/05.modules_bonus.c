#include "./main_bonus.h"

void	sema_waiter(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->philo_num)
		sem_wait(data->sem_all_eat);
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
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->start_eat_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	print_log(data, EATING);
	usleep(data->eating_time * 1000);
}

void	fork_down(t_data *data)
{
	if (++data->eat_count == data->eat_end)
		sem_post(data->sem_all_eat);
	sem_post(data->sem_forks);
	sem_post(data->sem_forks);
}
