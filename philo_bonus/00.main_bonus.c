
#include "./main_bonus.h"

void	init_sema(t_data *data)
{
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("all_eat");
	sem_open_hoook(&data->sem_print, "print", 1);
	sem_open_hoook(&data->sem_forks, "forks", data->philo_num);
	sem_open_hoook(&data->sem_all_eat, "all_eat", data->philo_num);
}

int	init(t_data *data, char **av, int ac)
{
	struct timeval	tv;

	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->eating_time = ft_atoi(av[3]);
	data->sleeping_time = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_end = ft_atoi(av[5]);
	else
		data->eat_end = -1;
	data->eat_count = 0;
	init_sema(data);
	data->start_time = get_time();
	data->start_eat_time = get_time();
	data->childs = malloc(sizeof(pid_t) * data->philo_num);
	if (!data->childs)
		on_error(MALLOC);
	return (1);
}

void	free_data(t_data *data)
{
	free(data->childs);
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("all_eat");
}

void	*all_full_checker(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	sema_waiter(data);
	sem_wait(data->sem_print);
	kill_all_childs(data);
	free_data(data);
	exit(0);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	is_all_full;
	int			i;
	int			status;

	if (!(ac == 5 || ac == 6))
		on_error(ARG);
	if (check_arg(av, ac) == 0)
		return (0);
	if (!init(&data, av, ac))
		return (0);
	sema_waiter(&data);
	i = 0;
	while (i < data.philo_num)
	{
		data.id = i;
		data.childs[i] = fork();
		if (data.childs[i] == 0)
			life(&data);
		i++;
	}
	pthread_create(&is_all_full, NULL, all_full_checker, &data);
	pthread_detach(is_all_full);
	waitpid(-1, &status, 0);
	kill_all_childs(&data);
	free_data(&data);
	return (0);
}
