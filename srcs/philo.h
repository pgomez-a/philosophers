/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:10:17 by pablo             #+#    #+#             */
/*   Updated: 2021/07/27 17:10:19 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_fork {
	int				mode;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_data {
	int		id;
	int		philo;
	int		death;
	int		eat;
	int		sleep;
	int		times;
	int		status;
	int		waiter;
	t_fork	*fork;
}	t_data;

typedef struct s_philo {
	int		id;
	int		left;
	int		right;
	t_data	*data;
}	t_philo;

/**
 ** philo.c
 **/

int		create_philo(t_data *data);

/**
 ** init_philo.c
 **/

int		init_forks(t_data *data, t_fork **fork);
int		init_threads(t_data *data, pthread_t **thread);
int		init_philos(t_data *data, t_fork **fork, t_philo **philo);

/**
 ** action_philo.c
 **/

void	philo_action(double tstamp, int time, char *action, t_philo *philo);
int		check_if_open(t_philo *philo);
int		check_if_dye(struct timeval *start, struct timeval *end,
			t_philo *philo);
int		waiter(t_data *data);

/**
 ** ph_utils.c
 **/

int		ph_error(char *str);
int		ph_free_error(t_fork **fk, t_philo **ph, pthread_t **th);
int		ph_sleep(int time);
int		ph_strcmp(char *strOne, char *strTwo);
long	ph_atoi(char *str);

#endif
