/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:07:34 by pablo             #+#    #+#             */
/*   Updated: 2021/07/27 17:08:39 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_action(int time, char *action, int id)
{
	struct timeval	gettime;
	double			time_stamp;

	gettimeofday(&gettime, NULL);
	time_stamp = ((double)gettime.tv_sec * 1000)
		+ ((double)gettime.tv_usec / 1000);
	printf("%ld %d %s\n", (long)time_stamp, id, action);
	if (time >= 0)
		ph_sleep(time);
}

int	waiter(t_data *waiter)
{
	while (1)
		;
	return (0);
}

void	*execute_philo(void *arg)
{
	struct timeval	start;
	struct timeval	end;
	t_philo			*philo;
	double			st;
	double			nd;

	philo = (t_philo *)arg;
	printf("id: %d\n", philo->id);
	//gettimeofday(&start, NULL);
	/*while (1)
	{
		if (philo->data->philo != 1 && philo->data->fork[philo->left].mode == 0 && philo->data->fork[philo->right].mode == 0)
		{
			if (philo->id % 2 == 0)
			{
				philo->data->fork[philo->left].mode = 1;
				pthread_mutex_lock(&(philo->data->fork[philo->left].mutex));
				philo_action(-1, "has taken a fork", philo->id);
				philo->data->fork[philo->right].mode = 1;
				pthread_mutex_lock(&(philo->data->fork[philo->right].mutex));
				philo_action(-1, "has taken a fork", philo->id);
			}
			else
			{
				philo->data->fork[philo->right].mode = 1;
				pthread_mutex_lock(&(philo->data->fork[philo->right].mutex));
				philo_action(-1, "has taken a fork", philo->id);
				philo->data->fork[philo->left].mode = 1;
				pthread_mutex_lock(&(philo->data->fork[philo->left].mutex));
				philo_action(-1, "has taken a fork", philo->id);
			}
			gettimeofday(&start, NULL);
			philo_action(philo->data->eat, "is eating", philo->id);
			philo->data->fork[philo->left].mode = 0;
			pthread_mutex_unlock(&(philo->data->fork[philo->left].mutex));
			philo->data->fork[philo->right].mode = 0;
			pthread_mutex_unlock(&(philo->data->fork[philo->right].mutex));
			philo_action(philo->data->sleep, "is sleeping", philo->id);
			philo_action(-1, "is thinking", philo->id);
		}
		gettimeofday(&end, NULL);
		st = ((double)start.tv_sec * 1000) + ((double)start.tv_usec / 1000);
		nd = ((double)end.tv_sec * 1000) + ((double)end.tv_usec / 1000);
		if ((long)(nd - st) > (long)philo->data->death)
		{
			philo_action(-1, "died", philo->id);
			exit(-1);
		}
	}*/
	return (0);
}

int	create_philo(t_data *data)
{
	pthread_t	*thread;
	t_philo		*philo;
	t_fork		*fork;
	int			count;

	if (init_forks(data, &fork) != 0)
		return (ph_free_error(&fork, &philo, &thread));
	if (init_threads(data, &thread) != 0)
		return (ph_free_error(&fork, &philo, &thread));
	if (init_philos(data, &fork, &philo) != 0)
		return (ph_free_error(&fork, &philo, &thread));
	count = 0;
	while (count < data->philo)
	{
		if (pthread_create(&thread[count], NULL,
				execute_philo, &philo[count]) != 0)
		{
			printf("Error Philo %d\n", philo[count].id);
			return (ph_free_error(&fork, &philo, &thread));
		}
		pthread_detach(thread[count]);
		count++;
	}
	return (waiter(data));
}
