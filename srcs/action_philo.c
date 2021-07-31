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
	pthread_mutex_t	mutex;
	struct timeval	gettime;
	double			time_stamp;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	gettimeofday(&gettime, NULL);
	time_stamp = ((double)gettime.tv_sec * 1000)
		+ ((double)gettime.tv_usec / 1000);
	if (philo->data->waiter == 1)
	{
		if (ph_strcmp("died", action) == 1)
			printf("\033[31m%ld %d %s\n\033[39m",
				(long)(time_stamp - tstamp), philo->id, action);
		else
			printf("%ld %d %s\n",
				(long)(time_stamp - tstamp), philo->id, action);
		if (time >= 0)
			ph_sleep(time);
	}
	pthread_mutex_unlock(&mutex);
}

/**
 ** Check if the forks are open to eat
 **/

int	check_if_open(t_philo *philo)
{
	if (philo->data->philo == 1)
		return (-1);
	if (philo->data->fork[philo->left].mode != 0)
		return (-1);
	if (philo->data->fork[philo->right].mode != 0)
		return (-1);
	return (0);
}

/**
 ** Check if a philo has died comparing the two time_stamps
 **/

int	check_if_dye(struct timeval *start, struct timeval *end, t_philo *philo)
{
	double		st;
	double		nd;

	st = ((double)start->tv_sec * 1000) + ((double)start->tv_usec / 1000);
	nd = ((double)end->tv_sec * 1000) + ((double)end->tv_usec / 1000);
	if ((long)(nd - st) > (long)philo->data->death)
	{
		philo_action(st, -1, "died", philo);
		return (-1);
	}
	return (0);
}

/**
 ** Main thread that manages the status of the threads
 **/

int	waiter(t_data *waiter)
{
	int	count;

	while (1)
	{
		if (waiter->status == 1)
		{
			waiter->waiter = 0;
			ph_sleep(2);
			count = 0;
			while (count < waiter->philo)
			{
				pthread_mutex_destroy(&(waiter->fork[count].mutex));
				count++;
			}
			return (-1);
		}
	}
	return (0);
}
