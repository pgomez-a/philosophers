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
		if (ph_strcmp("is eating", action) == 1)
			printf("\033[32m%ld %d %s\033[39m\n",
				(long)(time_stamp - tstamp), philo->id, action);
		else
			printf("%ld %d %s\n",
				(long)(time_stamp - tstamp), philo->id, action);
		if (philo->death->mode != 1 && time >= 0)
			ph_sleep(time);
	}
}
