/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_philos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:27:00 by pablo             #+#    #+#             */
/*   Updated: 2021/09/06 15:27:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 ** Kill all proccesses when all philos have eaten
 ** at least n times
 **/

static void	*count_times(void *arg)
{
	t_data	*data;
	int		count;

	data = *(t_data **)arg;
	count = 0;
	while (count < data->philo)
	{
		sem_wait(data->sem_times);
		count++;
	}
	count = 0;
	while (count < data->philo)
	{
		kill(data->pid_table[count], 9);
		count++;
	}
	sem_post(data->sem_times);
	return (NULL);
}

/**
 ** Manage the waiting for a death, so if a philo dye, the others
 ** dye too
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
	int	count;

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

/**
 ** Main process waits untill a philo died and stops the other
 **/

int	wait_for_childs(int size, t_data *data)
{
	pthread_t	*threads;
	pthread_t	times;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->philo);
	if (threads == NULL)
		return (-1);
	pthread_create(&times, NULL, count_times, &data);
	pthread_detach(times);
	manage_waiting(size, data->pid_table, data, threads);
	free(threads);
	free(data->pid_table);
	sem_close(data->sem_fork);
	sem_close(data->sem_waiter);
	sem_close(data->sem_print);
	sem_unlink("sem_philos");
	sem_unlink("sem_waiter");
	sem_unlink("sem_stdout");
	return (0);
}
