/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongolee <jongolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:59:58 by jongolee          #+#    #+#             */
/*   Updated: 2023/08/08 13:13:42 by jongolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

enum e_state {
	THINKING, 
	EATING, 
	SLEEPING, 
	DEAD,
	DONE
};

enum e_error {
	MALLOC,
	INPUT,
	ARG
};

typedef struct s_data
{
	//개별
	int					id;
	long long			start_time;
	//기본 정보
	int					time_to_die;
	int					eating_time;
	int					sleeping_time;
	int					must_eat;
	int					eat_counter;
	char				*fork;
	//모니터링
	int					philo_num;
	int					full_philo;
	int					over; > 다 먹거나 한명 죽거나
	pthread_mutex_t		id_mutex;
	pthread_mutex_t		fork_mutex;
	pthread_mutex_t		over_mutex;
}	t_data;

void	on_error(int ERROR_CODE);
int		is_input_valid(char *str, int i, int sign);
int		ft_atoi(char *str);
void	print_died(unsigned long sec, unsigned long usec, int id);
#endif