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

/**
 ** Locks two mutex to eat and close them in case one of them is not available
 **/

static int	close_forks(double time_stamp, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->data->fork[philo->left].mutex));
		pthread_mutex_lock(&(philo->data->fork[philo->right].mutex));
	}
	else
	{
		pthread_mutex_lock(&(philo->data->fork[philo->right].mutex));
		pthread_mutex_lock(&(philo->data->fork[philo->left].mutex));
	}
	if (check_if_open(philo) == 0)
	{
		philo->data->fork[philo->left].mode = 1;
		philo_action(time_stamp, -1, "has taken a fork", philo);
		philo->data->fork[philo->right].mode = 1;
		philo_action(time_stamp, -1, "has taken a fork", philo);
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->fork[philo->left].mutex));
	pthread_mutex_unlock(&(philo->data->fork[philo->right].mutex));
	return (-1);
}

/**
 ** Unlock two mutex in case a philo has stop eating
 **/

static void	open_forks(t_philo *philo)
{
	philo->data->fork[philo->left].mode = 0;
	pthread_mutex_unlock(&(philo->data->fork[philo->left].mutex));
	philo->data->fork[philo->right].mode = 0;
	pthread_mutex_unlock(&(philo->data->fork[philo->right].mutex));
}

/**
 ** Function that a philo executes while waiter manages its values
 **/

void	*execute_philo(void *arg)
{
	struct timeval	start;
	double			time_stamp;
	t_philo			*philo;

	philo = (t_philo *)arg;
	gettimeofday(&start, NULL);
	philo->data->time[philo->id - 1].time = start;
	time_stamp = ((double)start.tv_sec * 1000)
		+ ((double)start.tv_usec / 1000);
	philo->data->time[philo->id - 1].tstamp = time_stamp;
	while (philo->data->waiter == 1)
	{
		if (philo->data->philo != 1 && close_forks(time_stamp, philo) == 0)
		{
			//gettimeofday(&end, NULL);
			//if (check_if_dye(&start, &end, philo) != 0)
			//	philo->data->status = 1;
			gettimeofday(&start, NULL);
			philo->data->time[philo->id - 1].time = start;
			philo_action(time_stamp, philo->data->eat, "is eating", philo);
			open_forks(philo);
			philo_action(time_stamp, philo->data->sleep, "is sleeping", philo);
			philo_action(time_stamp, -1, "is thinking", philo);
		}
		//gettimeofday(&end, NULL);
		//if (check_if_dye(&start, &end, philo) != 0)
		//	philo->data->status = 1;
	}
	return (NULL);
}

/**
 ** Init the values of the philos and create them to start eating,
 ** sleeping and thinking
 **/

int	create_philo(t_data *data)
{
	pthread_t	*thread;
	t_philo		*philo;
	t_time		*time;
	t_fork		*fork;
	int			count;

	if (init_forks(data, &fork) != 0)
		return (ph_free_error(&fork, &philo, &time, &thread));
	if (init_threads(data, &thread) != 0)
		return (ph_free_error(&fork, &philo, &time, &thread));
	if (init_tstamps(data, &time) != 0)
		return (ph_free_error(&fork, &philo, &time, &thread));
	if (init_philos(data, &fork, &time, &philo) != 0)
		return (ph_free_error(&fork, &philo, &time, &thread));
	count = 0;
	while (count < data->philo)
	{
		if (pthread_create(&thread[count], NULL,
				execute_philo, &philo[count]) != 0)
		{
			printf("Error Philo %d\n", philo[count].id);
			return (ph_free_error(&fork, &philo, &time, &thread));
		}
		pthread_detach(thread[count]);
		count++;
	}
	return (waiter(data));
}
