#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUMBER_PHILO 10

typedef struct	s_data {
	int	eat;
	int	death;
	int	status;
}	t_data;

typedef struct s_philo {
	int	id;
	t_data	*data;
}	t_philo;

int	waiter(t_data *waiter)
{
	while (1)
	{
		if (waiter->status != 0)
			return (-1);
	}
	return (0);
}

void	*imprimir(void *arg)
{
	t_philo	*philo;
	int	tot;
	int	count;

	philo = (t_philo *)arg;
	count = 0;
	while (1)
	{
		printf("id: %d --> %d\n", philo->id, philo->data->eat);
		if (count == 100)
			philo->data->status = 1;
		count++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread[NUMBER_PHILO];
	t_philo		philo[NUMBER_PHILO];
	t_data		data;
	int		count;
	int		id;

	count = 0;
	data.eat = 0;
	data.death = 0;
	data.status = 0;
	while (count < NUMBER_PHILO)
	{
		philo[count].id = count + 1;
		philo[count].data = &data;
		if (pthread_create(&thread[count], NULL, imprimir, &philo[count]) != 0)
		{
			printf("Error %d\n", count);
			return (-1);
		}
		pthread_detach(thread[count]);
		count++;
	}
	return (waiter(&data));
}
