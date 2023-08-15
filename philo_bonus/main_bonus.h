#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

enum e_error {
	MALLOC,
	INPUT,
	ARG,
	SEMA,
	MUTEX
};

enum e_log {
	FORK,
	EATING,
	SLEEPING,
	THINKING
};

typedef struct s_data
{
	int			id;
	//인자 5개
	int			philo_num;
	int			time_to_die;
	int			eating_time;
	int			sleeping_time;
	//배부른 횟수
	int			eat_end;
	int			eat_count;
	//시작 시간 > 시간 경과 출력용
	long long	start_time;
	//처음 먹은 시간
	long long	start_eat_time;
	//죽으면 종료되는거 감지, sema 0짜리
	pid_t		*childs;
	//print lock, sema 1짜리
	sem_t		*sem_print;
	//포크 가져갈 떄 wait, 다 먹고 post
	sem_t		*sem_forks;
	//다 먹으면 종료, wait 50번
	sem_t		*sem_all_eat;
	//자다 죽는거 감시
}	t_data;

//parse
int		check_arg(char **av, int ac);
int		is_input_valid(char *str, int i, int sign);
int		ft_atoi(char *str);

//error
void	on_error(int ERROR_CODE);

//hooks
void	sem_open_hoook(sem_t **sema, const char *str, unsigned int sema_num);

//module
void	life(t_data *data);
void	kill_all_childs(t_data *data);

void	fork_up(t_data *data);
void	eating(t_data *data);
void	fork_down(t_data *data);
void	print_log(t_data *data, int LOG_MSG);
void	sema_waiter(t_data *data);
#endif