#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data {
	int				fork;
	int				id;
	int				philo;
	int				death;
	int				eat;
	int				sleep;
	int				times;
}	t_data;

/**
 ** philo.c
 **/

void	create_philo(t_data *data);

/**
 ** ph_utils.c
 **/

int		ph_error(char *str);
int		ph_sleep(int time);
long	ph_atoi(char *str);

#endif
