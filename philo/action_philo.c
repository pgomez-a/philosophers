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
	int				unlock;

	pthread_mutex_lock(&(philo->data->print_mut));
	gettimeofday(&gettime, NULL);
	time_stamp = ((double)gettime.tv_sec * 1000)
		+ ((double)gettime.tv_usec / 1000);
	unlock = 0;
	if (philo->data->waiter != 1)
	{
		if (ph_strcmp("is eating", action) == 1)
			printf("\033[32m%ld %d %s\033[39m\n",
				(long)(time_stamp - tstamp), philo->id, action);
		else
			printf("%ld %d %s\n",
				(long)(time_stamp - tstamp), philo->id, action);
		pthread_mutex_unlock(&(philo->data->print_mut));
		unlock = 1;
		if (philo->data->waiter != 1 && time >= 0)
			ph_sleep(time);
	}
	if (unlock == 0)
		pthread_mutex_unlock(&(philo->data->print_mut));
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

static int	manage_philo_death(int mode, int count, double nd, t_data *waiter)
{
	pthread_mutex_lock(&(waiter->print_mut));
	waiter->waiter = 1;
	if (mode == 1)
	{
		printf("\033[31m%ld %d died\033[39m\n",
			(long)(nd - waiter->time[count].tstamp), count + 1);
	}
	ph_sleep(2);
	pthread_mutex_unlock(&(waiter->print_mut));
	count = 0;
	while (count < waiter->philo)
	{
		pthread_mutex_destroy(&(waiter->fork[count].mutex));
		count++;
	}
	pthread_mutex_unlock(&(waiter->mutex));
	pthread_mutex_destroy(&(waiter->print_mut));
	pthread_mutex_destroy(&(waiter->mutex));
	ph_sleep(2);
	if (mode == 1)
		return (1);
	return (0);
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
			if (waiter->time[count].id > 0 && (long)(nd - st) > waiter->death)
				return (manage_philo_death(1, count, nd, waiter));
			pthread_mutex_unlock(&(waiter->mutex));
			if (waiter->waiter == waiter->philo * -1)
				return (manage_philo_death(0, count, nd, waiter));
			count++;
		}
	}
	return (0);
}
