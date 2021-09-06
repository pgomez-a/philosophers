/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:28:56 by pablo             #+#    #+#             */
/*   Updated: 2021/09/03 13:29:42 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 ** Print a message when a philo is going to do an action
 ** Wait if philo has to sleep or eat
 **/

void	philo_action(double tstamp, int time, char *action, t_philo *philo)
{
	struct timeval	gettime;
	double			time_stamp;

	gettimeofday(&gettime, NULL);
	time_stamp = ((double)gettime.tv_sec * 1000)
		+ ((double)gettime.tv_usec / 1000);
	if (philo->death->mode != 1)
	{
		sem_wait(philo->data->sem_print);
		if (ph_strcmp("is eating", action) == 1)
			printf("\033[32m%ld %d %s\033[39m\n",
				(long)(time_stamp - tstamp), philo->id, action);
		else
			printf("%ld %d %s\n",
				(long)(time_stamp - tstamp), philo->id, action);
		sem_post(philo->data->sem_print);
		if (philo->death->mode != 1 && time >= 0)
			ph_sleep(time);
	}
}

/**
 ** Init an array of pids that are going to be created
 ** Open a semaphore with a value of the total amount of philos
 **/

int	init_values(t_data *data)
{
	data->pid_table = (pid_t *)malloc(sizeof(pid_t) * data->philo);
	if (data->pid_table == NULL)
		return (-1);
	sem_close(data->sem_fork);
	sem_close(data->sem_waiter);
	sem_close(data->sem_times);
	sem_close(data->sem_print);
	sem_unlink("sem_philos");
	sem_unlink("sem_waiter");
	sem_unlink("sem_times");
	sem_unlink("sem_stdout");
	data->sem_fork = sem_open("sem_philos", O_CREAT, 0666, data->philo);
	data->sem_waiter = sem_open("sem_waiter", O_CREAT, 0666, data->philo / 2);
	data->sem_times = sem_open("sem_times", O_CREAT, 0666, 0);
	data->sem_print = sem_open("sem_stdout", O_CREAT, 0666, 1);
	return (0);
}
