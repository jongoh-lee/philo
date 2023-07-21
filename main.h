/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongolee <jongolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:59:58 by jongolee          #+#    #+#             */
/*   Updated: 2023/07/21 21:03:29 by jongolee         ###   ########.fr       */
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
	INPUT
};

typedef struct s_data
{
	int					id;
	int					philo_num;
	int					time_to_die;
	int					eating_time;
	int					sleeping_time;
	int					must_eat;
	int					eat_counter;
	pthread_mutex_t		mutex;
	//업데이트
	int					*state;
	unsigned long		*last_eat_start_sec;
	unsigned long		*last_eat_start_usec;
}	t_data;

int	is_input_valid(char *str, int i, int sign);
int	ft_atoi(const char *str);
void	on_error(int ERROR_CODE);
void	print_died(unsigned long sec, unsigned long usec, int id);
#endif