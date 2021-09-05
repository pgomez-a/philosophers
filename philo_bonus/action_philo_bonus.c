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

int	init_values(pid_t **pid_table, t_data *data)
{
	(*pid_table) = (pid_t *)malloc(sizeof(pid_t) * data->philo);
	if (pid_table == NULL)
		return (-1);
	sem_close(data->sem_fork);
	sem_close(data->sem_waiter);
	sem_close(data->sem_print);
	sem_unlink("sem_philos");
	sem_unlink("sem_waiter");
	sem_unlink("sem_stdout");
	data->sem_fork = sem_open("sem_philos", O_CREAT, 0666, data->philo);
	data->sem_waiter = sem_open("sem_waiter", O_CREAT, 0666, data->philo / 2);
	data->sem_print = sem_open("sem_stdout", O_CREAT, 0666, 1);
	return (0);
}

/**
 ** Make main process wait untill their childs have finished
 **/

static void	*waitpid_per_philo(void *arg)
{
	pid_t	*pid;

	pid = (pid_t *)arg;
	waitpid(*pid, NULL, 0);
	(*pid) = -1;
	return (NULL);
}

static void	manage_waiting(int size, pid_t *pid_table,
		t_data *data, pthread_t *threads)
{
	int			count;

	count = 0;
	while (count < size)
	{
		pthread_create(&threads[count], NULL, waitpid_per_philo,
			&pid_table[count]);
		pthread_detach(threads[count]);
		count++;
	}
	count = 0;
	while (pid_table[count] > 0)
	{
		count++;
		if (count == data->philo)
			count = 0;
	}
	count = 0;
	while (count < size)
	{
		if (pid_table[count] > 0)
			kill(pid_table[count], 9);
		count++;
	}
}

int	wait_for_childs(int size, pid_t *pid_table, t_data *data)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->philo);
	if (threads == NULL)
		return (-1);
	manage_waiting(size, pid_table, data, threads);
	free(threads);
	free(pid_table);
	sem_close(data->sem_fork);
	sem_close(data->sem_waiter);
	sem_close(data->sem_print);
	sem_unlink("sem_philos");
	sem_unlink("sem_waiter");
	sem_unlink("sem_stdout");
	return (0);
}
