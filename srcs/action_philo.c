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

void	philo_action(int id, int time, char *action)
{
	struct timeval	gettime;
	double			time_stamp;

	gettimeofday(&gettime, NULL);
	time_stamp = ((double)gettime.tv_sec * 1000)
		+ ((double)gettime.tv_usec / 1000);
	printf("%ld %d %s\n", (long)time_stamp, id, action);
	if (time >= 0)
		ph_sleep(time);
}

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

int	check_if_dye(struct timeval *start, struct timeval *end, t_philo *philo)
{
	double		st;
	double		nd;

	st = ((double)start->tv_sec * 1000) + ((double)start->tv_usec / 1000);
	nd = ((double)end->tv_sec * 1000) + ((double)end->tv_usec / 1000);
	if ((long)(nd - st) > (long)philo->data->death)
	{
		philo_action(philo->id, -1, "died");
		return (-1);
	}
	return (0);
}

int	waiter(t_data *waiter)
{
	while (1)
		;
	return (0);
}
