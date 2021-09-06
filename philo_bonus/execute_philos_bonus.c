/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_philos_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:29:09 by pablo             #+#    #+#             */
/*   Updated: 2021/09/06 15:26:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 ** Check the difference between the last meal of a philo and
 ** the current time to determine if the philo is dead.
 **/

static void	*check_if_dead(void *arg)
{
	struct timeval	time_stamp;
	double			time;
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		gettimeofday(&time_stamp, NULL);
		time = ((double)time_stamp.tv_sec * 1000)
			+ ((double)time_stamp.tv_usec / 1000);
		if ((long)(time - philo->death->time) > (long)philo->data->death)
		{
			sem_wait(philo->data->sem_print);
			philo->death->mode = 1;
			printf("\033[31m%ld %d died \033[39m\n",
				(long)(time - philo->death->start), philo->id);
			exit(1);
		}
	}
	return (NULL);
}

/**
 ** Take two forks before start eating
 **/

static void	take_forks(double start, t_philo *philo)
{
	sem_wait(philo->data->sem_waiter);
	sem_wait(philo->data->sem_fork);
	philo_action(start, -1, "has taken a fork", philo);
	sem_wait(philo->data->sem_fork);
	philo_action(start, -1, "has taken a fork", philo);
	sem_post(philo->data->sem_waiter);
}

static void	eat_sleep_wait(double start, struct timeval *time_stamp,
		t_philo *philo)
{
	gettimeofday(time_stamp, NULL);
	philo->death->time = ((double)time_stamp->tv_sec * 1000)
		+ ((double)time_stamp->tv_usec / 1000);
	philo_action(start, philo->data->eat, "is eating", philo);
	sem_post(philo->data->sem_fork);
	sem_post(philo->data->sem_fork);
	philo_action(start, philo->data->sleep, "is sleeping", philo);
	philo_action(start, -1, "is thinking", philo);
}

/**
 ** Once a philo is created, it starts eating, sleeping and thinking
 **/
int	execute_philo(t_philo *philo)
{
	struct timeval	time_stamp;
	double			start;
	t_death			death;
	pthread_t		thread;
	int				times;

	gettimeofday(&time_stamp, NULL);
	start = ((double)time_stamp.tv_sec * 1000)
		+ ((double)time_stamp.tv_usec / 1000);
	death.time = start;
	death.start = start;
	death.mode = 0;
	philo->death = &death;
	pthread_create(&thread, NULL, check_if_dead, philo);
	pthread_detach(thread);
	times = philo->data->times;
	while (philo->death->mode != 1)
	{
		take_forks(start, philo);
		if (times == 0)
			sem_post(philo->data->sem_times);
		eat_sleep_wait(start, &time_stamp, philo);
		times--;
	}
	return (1);
}
