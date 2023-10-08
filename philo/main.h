/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:36:27 by jongohlee         #+#    #+#             */
/*   Updated: 2023/10/08 18:49:25 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

enum e_error {
	MALLOC,
	INPUT,
	ARG
};

enum e_log {
	FORK,
	EATING,
	SLEEPING,
	THINKING
};

typedef struct s_data
{
	char				is_died;
	int					id;
	int					time_to_die;
	int					eating_time;
	int					sleeping_time;
	int					*eat_count;
	int					eat_end;
	int					philo_num;
	long long			start_time;
	long long			*start_eat_time;
	char				*forks;
	int					full_philo;
	pthread_mutex_t		id_mutex;
	pthread_mutex_t		*fork_mutexes;
	pthread_mutex_t		over_mutex;
	pthread_mutex_t		ready_mutex;
	pthread_mutex_t		full_mutex;
	pthread_mutex_t		time_mutex;
}	t_data;

//parse
int			check_arg(char **av, int ac);
int			is_input_valid(char *str, int i, int sign);
int			ft_atoi(char *str);
//error
void		on_error(int ERROR_CODE);

//module1
void		print_log(t_data *data, int LOG_MSG, int id);
void		make_philos(t_data *data, pthread_t **threads);
void		monitor_philos(t_data *data, int i, long long now);
long long	get_time(void);
void		ft_sleep(long long time, int last);
//module2
void		eating(t_data *data, int id);
void		fork_up(t_data *data, int id);
void		fork_down(t_data *data, int id);
#endif