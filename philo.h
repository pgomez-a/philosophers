#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct data_s {
	pthread_mutex_t	mutex;
	int		pos;
	int		philo;
	int		death;
	int		eat;
	int		sleep;
	int		times;
}	data_t;

/**
 ** philo.c
 **/

void	create_philo(data_t *data);

/**
 ** ph_utils.c
 **/

int	ph_error(char *str);
long	ph_atoi(char *str);

#endif
