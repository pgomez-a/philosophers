/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:29:06 by pablo             #+#    #+#             */
/*   Updated: 2021/09/03 13:29:38 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 ** Output an error message within a return
 **/

int	ph_error(char *str)
{
	printf("\033[31mError\033[95m\n");
	printf("\033[31m%s\033[95m\n", str);
	return (1);
}

/**
 ** Simulate usleep function with less delay using miliseconds
 ** instead of microseconds
 **/

int	ph_sleep(int time)
{
	struct timeval	start;
	struct timeval	end;
	double			st;
	double			nd;

	if (time < 0)
		return (-1);
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	st = ((double)start.tv_sec * 1000) + ((double)start.tv_usec / 1000);
	nd = ((double)end.tv_sec * 1000) + ((double)end.tv_usec / 1000);
	while (nd - st < (double)time)
	{
		gettimeofday(&end, NULL);
		nd = ((double)end.tv_sec * 1000) + ((double)end.tv_usec / 1000);
	}
	return (0);
}

/**
 ** Pass from type char to type int
 **/

long	ph_atoi(char *str)
{
	long	out;
	long	neg;
	int		count;

	if (str == NULL)
		return (-1);
	count = 0;
	out = 0;
	neg = 1;
	while (str[count] && str[count] == ' ')
		count++;
	if (str[count] == '+' || str[count] == '-')
	{
		if (str[count] == '-')
			neg = -1;
		count++;
	}
	while (str[count])
	{
		if (str[count] < '0' || str[count] > '9')
			return (-1);
		out = (out * 10) + (str[count] - '0');
		count++;
	}
	return (out * neg);
}

/**
 ** Compare if you strings are equal
 **/

int	ph_strcmp(char *strOne, char *strTwo)
{
	int	count;

	count = 0;
	while (strOne[count] && strTwo[count])
	{
		if (strOne[count] != strTwo[count])
			return (-1);
		count++;
	}
	if (strOne[count] != '\0' || strTwo[count] != '\0')
		return (-1);
	return (1);
}
