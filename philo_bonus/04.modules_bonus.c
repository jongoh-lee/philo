#include "./main_bonus.h"


//철학자는 잠을자고 빨리 돌아와야 본인이 살 수 있지만, 확인은 많이 하면 남들이 죽을 수 있다.
void	ft_usleep(long long start, int last)
{
	while (1)
	{
		if (get_time() - start > last * 1000)
			break ;
		usleep(800);
	}
}

//내 자신이 살았는지 죽었는지 확인은 자주하지 않아도 되지만 10ms안에 출력해야 한다.
void	*monitor(void	*arg)
{
	t_data			*data;
	long long		now;

	data = (t_data*)arg;
	while (1)
	{
		now = get_time();
		if (now - data->eat_start_time > data->life_time * 1000)
		{
			sem_wait(data->sem_print);
			printf("%lld %d died\n", (now - data->start_time) / 1000, data->id + 1);
			exit(0);
		}
		usleep(500);
	}
}

void	life(t_data *data)
{
	pthread_t	full_monitor;

	sem_wait(data->sem_ready);
	sem_post(data->sem_ready);
	data->start_time = data->init + 6000000;
	//마지막이 앉을때 까지 걸리는 시간을 고려해서 시작은 빨리 한다.
	while (1)
	{
		if (get_time() >= data->start_time)
			break ;
		else
			usleep(480);
	}
	// data->start_time = get_time();
	data->eat_start_time = data->start_time;
	if (pthread_create(&full_monitor, NULL, monitor, data) != 0)
		on_error(MUTEX);
	if (pthread_detach(full_monitor) != 0)
		on_error(MUTEX);
	while (1)
	{
		fork_up(data);
		eating(data);
		fork_down(data);
		print_log(data, SLEEPING);
		ft_usleep(get_time(), data->sleeping_time);
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

void	print_log(t_data *data, int LOG_MSG)
{
	long long		now;

	sem_wait(data->sem_print);
	now = (get_time() - data->start_time) / 1000;
	if (LOG_MSG == FORK)
		printf("%lld %d has taken a fork\n", now, data->id + 1);
	else if (LOG_MSG == EATING)
		printf("%lld %d is eating\n", now, data->id + 1);
	else if (LOG_MSG == SLEEPING)
		printf("%lld %d is sleeping\n", now, data->id + 1);
	else if (LOG_MSG == THINKING)
		printf("%lld %d is thinking\n", now, data->id + 1);
	sem_post(data->sem_print);
}