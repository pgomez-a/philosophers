/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:44:26 by pablo             #+#    #+#             */
/*   Updated: 2021/07/28 14:44:27 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (philo->data->waiter == 0)
	{
		printf("%ld %d %s\n", (long)(time_stamp - tstamp), philo->id, action);
		if (time >= 0)
			ph_sleep(time);
	}
}

/**
 ** Check if the forks are open to eat
 **/

int	check_if_open(t_philo *philo)
{
	if (philo->data->fork[philo->left].mode != 0)
		return (-1);
	if (philo->data->fork[philo->right].mode != 0)
		return (-1);
	return (0);
}

/**
 ** Main thread that manages the status of the threads
 **/

static int	manage_philo_death(int count, double nd, t_data *waiter)
{
	waiter->waiter = 1;
	printf("\033[31m%ld %d is died\033[39m\n",
		(long)(nd - waiter->time[count].tstamp), count + 1);
	ph_sleep(2);
	count = 0;
	while (count < waiter->philo)
	{
		pthread_mutex_destroy(&(waiter->fork[count].mutex));
		count++;
	}
	pthread_mutex_destroy(&(waiter->mutex));
	return (1);
}

int	waiter(t_data *waiter)
{
	struct timeval	start;
	struct timeval	end;
	double			st;
	double			nd;
	int				count;

	while (1)
	{
		count = 0;
		while (count < waiter->philo)
		{
			gettimeofday(&end, NULL);
			nd = ((double)end.tv_sec * 1000) + ((double)end.tv_usec / 1000);
			pthread_mutex_lock(&(waiter->mutex));
			start = waiter->time[count].time;
			st = ((double)start.tv_sec * 1000) + ((double)start.tv_usec / 1000);
			pthread_mutex_unlock(&(waiter->mutex));
			if (st != 0 && nd - st > waiter->death)
				return (manage_philo_death(count, nd, waiter));
			if (waiter->waiter == waiter->philo * -1)
				return (0);
			count++;
		}
	}
	return (0);
}
