#include "./main_bonus.h"

void	*monitor(void	*arg)
{
	t_data			*data;
	struct timeval	tv;
	long long		now;

	data = (t_data*)arg;
	while (1)
	{
		usleep(50);
		gettimeofday(&tv, NULL);
		now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (now - data->start_eat_time >= data->time_to_die)
		{
			sem_wait(data->sem_print);
			printf("%lld %d died\n", (now - data->start_time), data->id + 1);
			exit(0);
		}
	}
}

void	life(t_data *data)
{
	pthread_t	full_monitor;

	if (pthread_create(&full_monitor, NULL, monitor, data) != 0)
		on_error(MUTEX);
	if (pthread_detach(full_monitor) != 0)
		on_error(MUTEX);
	if (data->id % 2 == 1)
		usleep(data->eating_time * 500);
	while (1)
	{
		fork_up(data);
		eating(data);
		fork_down(data);
		print_log(data, SLEEPING);
		print_log(data, THINKING);
	}
}

void	kill_all_childs(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
	{
		kill(data->childs[i], SIGKILL);
		i++;
	}
}

void	print_log2(int LOG_MSG, int id, long long now)
{
	if (LOG_MSG == SLEEPING)
		printf("%lld %d is sleeping\n", now, id + 1);
	else if (LOG_MSG == THINKING)
		printf("%lld %d is thinking\n", now, id + 1);
}

void	print_log(t_data *data, int LOG_MSG)
{
	struct timeval	tv;
	long long		now;

	sem_wait(data->sem_print);
	gettimeofday(&tv, NULL);
	now = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - data->start_time;
	if (LOG_MSG == FORK)
		printf("%lld %d has taken a fork\n", now, data->id + 1);
	else if (LOG_MSG == EATING)
		printf("%lld %d is eating\n", now, data->id + 1);
	else
		print_log2(LOG_MSG, data->id, now);
	sem_post(data->sem_print);
}