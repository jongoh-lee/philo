/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04.module.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongohlee <jongohlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:52:47 by jongohlee         #+#    #+#             */
/*   Updated: 2023/08/10 02:38:15 by jongohlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	fork_up(t_data *data, int id)
{
	while (1)
	{
		pthread_mutex_lock(&data->fork_mutex);
		if (data->forks[(id-1)] == 1 && data->forks[id % data->philo_num] == 1)
		{
			pthread_mutex_lock(&data->over_mutex);
			if (!data->is_over)
			{
				data->forks[(id-1)] = 0;
				print_log(data, FORK, id);
				data->forks[id % data->philo_num] = 0;
				print_log(data, FORK, id);
				pthread_mutex_unlock(&data->over_mutex);
				pthread_mutex_unlock(&data->fork_mutex);
				break ;
			}
			pthread_mutex_unlock(&data->over_mutex);
		}
		pthread_mutex_unlock(&data->fork_mutex);
	}
//포크 확인
//포크 들기
}

void	fork_down(t_data *data, int id)
{
	pthread_mutex_lock(&data->fork_mutex);
	data->forks[(id-1)] = 1;
	data->forks[id % data->philo_num] = 1;
	pthread_mutex_unlock(&data->fork_mutex);
}

void	eating(t_data *data, int id)
{
	struct timeval	tv;
//먹는중 출력
//먹은 횟수 증가
//먹은 횟수가 배부른것과 같다면 배부른 필로 +1
//배부른 필로가 전체 숫자와 같다면 is_over = 1;
	//이렇게 해야 먹는중을 더 빈번하게 호출할 수 있다.
	pthread_mutex_lock(&data->over_mutex);
	if (!data->is_over)
		print_log(data, EATING, id);
	pthread_mutex_unlock(&data->over_mutex);
	//시간 업데이트
	gettimeofday(&tv, NULL);
	data->start_eat_time[id-1] = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (++data->eat_count[id-1] == data->eat_end)
	{
		pthread_mutex_lock(&data->full_mutex);
		data->full_philo++;
		if (data->full_philo == data->philo_num)
		{
			pthread_mutex_lock(&data->over_mutex);
			data->is_over = 1;
			pthread_mutex_unlock(&data->over_mutex);
		}
		pthread_mutex_unlock(&data->full_mutex);
	}
	// pthread_mutex_lock(&data->over_mutex);
	// if (!data->is_over)
	// 	print_log(data, EATING, id);
	// if (++data->eat_count[id-1] == data->eat_end)
	// {
	// 	pthread_mutex_lock(&data->full_mutex);
	// 	data->full_philo++;
	// 	if (data->full_philo == data->philo_num)
	// 		data->is_over = 1;
	// 	pthread_mutex_unlock(&data->full_mutex);
	// }
	// pthread_mutex_unlock(&data->over_mutex);
}

void	sleeping(t_data *data, int id)
{
	pthread_mutex_lock(&data->over_mutex);
	if (!data->is_over)
		print_log(data, SLEEPING, id);
	pthread_mutex_unlock(&data->over_mutex);
}

void	thinking(t_data *data, int id)
{
	pthread_mutex_lock(&data->over_mutex);
	if (!data->is_over)
		print_log(data, THINKING, id);
	pthread_mutex_unlock(&data->over_mutex);
}

