/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:59:58 by jongolee          #+#    #+#             */
/*   Updated: 2023/08/10 16:47:54 by jongohlee        ###   ########.fr       */
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
	// 1.개별 자원 > 각각의 철학자가 접근하는 영역, 외부 접근 안함
	int					id;
	//  - 기본 정보 생명, 식사 시간, 자는 시간, 종료 횟수, 먹은 횟수
	int					time_to_die;
	int					eating_time;
	int					sleeping_time;
	int					*eat_count;
	int					eat_end;
	//다 먹었는지 모니터 philo_num == *full_philo;
	int					philo_num;
	//배열 부분
	// 1. 먹기 시작하면 시간 업데이트
	long long			start_time;
	long long			*start_eat_time;
	// 2. 포크를 들기 전 공유 자원 접근
	char				*forks;
	//종료를 확안하는 1개 flag
	char				is_over;
	//배부른 철학자가 전체 철학자와 같으면 종료, is_over == 1;
	int					full_philo;
	//처음 아이디 설정만 함
	pthread_mutex_t		id_mutex;
	pthread_mutex_t		*fork_mutexes;
	//각각의 출력 전에 확인, 모든 영역에 lock을 걸게 되면 sleep을 만나 lock을 취득하고 대기상태로 빠짐
	pthread_mutex_t		over_mutex;
	//다 먹고 난 후 각각의 철학자가 더하기 1;
	pthread_mutex_t		full_mutex;
}	t_data;

//parse
int		check_arg(char **av, int ac);
int		is_input_valid(char *str, int i, int sign);
int		ft_atoi(char *str);
//error
void	on_error(int ERROR_CODE);

//module1
void	print_log(t_data *data, int LOG_MSG, int id);
void	make_philos(t_data *data, pthread_t **threads);
void	monitor_philos(t_data *data);
//module2
void	eating(t_data *data, int id);
void	fork_up(t_data *data, int id);
void	fork_down(t_data *data, int id);
#endif