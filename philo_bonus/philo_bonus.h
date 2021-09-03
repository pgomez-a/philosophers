/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:29:34 by pablo             #+#    #+#             */
/*   Updated: 2021/09/03 13:29:35 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data {
	int				philo;
	int				death;
	int				eat;
	int				sleep;
	int				times;
}	t_data;

typedef struct s_death {
	int		mode;
	double	time;
	double	start;
}	t_death;

typedef struct s_philo {
	int		id;
	t_data	*data;
	t_death	*death;
}	t_philo;

/**
 ** philo_bonus.c
 **/

int		create_philo(t_data *data);

/**
 ** action_philo_bonus.c
 **/

void	philo_action(double tstamp, int time, char *action, t_philo *philo);

/**
 ** ph_utils_bonus.c
 **/

int		ph_error(char *str);
int		ph_sleep(int time);
int		ph_strcmp(char *strOne, char *strTwo);
long	ph_atoi(char *str);

#endif
