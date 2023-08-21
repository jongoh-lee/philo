#include "./main.h"

int	init(t_data *data, pthread_t **threads, char **av, int ac)
{
	data->id = 0;
	data->is_ready = 0;
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
	pthread_mutex_init(&data->over_mutex, NULL);
	pthread_mutex_init(&data->full_mutex, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	data->full_philo = 0;
	// data->start_time = get_time();
	data->start_eat_time = malloc(sizeof(long long) * data->philo_num);
	data->forks = malloc(sizeof(char) * data->philo_num);
	data->eat_count = malloc(sizeof(int) * data->philo_num);
	*threads = malloc(sizeof(pthread_t) * data->philo_num);
	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!(data->start_eat_time || data->forks || data->eat_count \
	|| data->fork_mutexes || *threads))
		on_error(MALLOC);
	return (1);
}

void	detach_philos(pthread_t **threads, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
	{
		if (pthread_detach((*threads)[i]) != 0)
			return ;
		i++;
	}
}

void	free_data(t_data *data, pthread_t **threads)
{
	free(data->start_eat_time);
	free(data->forks);
	free(*threads);
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->id_mutex);
	pthread_mutex_destroy(&data->over_mutex);
	pthread_mutex_destroy(&data->full_mutex);
	pthread_mutex_destroy(&data->time_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->fork_mutexes[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	// atexit(hi);
	pthread_t	*threads;
	t_data		data;

	if (!(ac == 5 || ac == 6))
		on_error(ARG);
	if (check_arg(av, ac) == 0)
		return (0);
	if (!init(&data, &threads, av, ac))
		return (0);
	make_philos(&data, &threads);
	detach_philos(&threads, data.philo_num);
	while (1)
	{
		if (data.is_ready)
			break ;
		else
			usleep(1);
	}
	monitor_philos(&data, 0);
	usleep((data.eating_time + data.sleeping_time) * 2000);
	mutex_destroy(&data);
	free_data(&data, &threads);
	return (0);
}
