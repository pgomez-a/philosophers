/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:52:05 by pablo             #+#    #+#             */
/*   Updated: 2021/07/27 17:52:07 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 ** Start the forks with off mode and a mutex to lock when needed
 **/

int	init_forks(t_data *data, t_fork **fork)
{
	int	count;

	(*fork) = (t_fork *)malloc(sizeof(t_fork) * data->philo);
	if (*fork == NULL)
		return (-1);
	count = 0;
	while (count < data->philo)
	{
		(*fork)[count].mode = 0;
		pthread_mutex_init(&((*fork)[count].mutex), NULL);
		count++;
	}
	return (0);
}

/**
 ** Allocate memory for threads when creating them
 **/

int	init_threads(t_data *data, pthread_t **thread)
{
	(*thread) = (pthread_t *)malloc(sizeof(pthread_t) * data->philo);
	if (*thread == NULL)
		return (-1);
	return (0);
}

/**
 ** Init values of philos before creating them
 **/

int	init_philos(t_data *data, t_fork **fork, t_philo **philo)
{
	int	count;

	(*philo) = (t_philo *)malloc(sizeof(t_philo) * data->philo);
	if (*philo == NULL)
		return (-1);
	data->fork = *fork;
	count = 0;
	while (count < data->philo)
	{
		(*philo)[count].id = count + 1;
		(*philo)[count].data = data;
		(*philo)[count].left = count;
		if ((*philo)[count].id == data->philo)
			(*philo)[count].right = 0;
		else
			(*philo)[count].right = count + 1;
		count++;
	}
	return (0);
}
