#include "philo.h"

void	*philo(void *arg)
{
	data_t	*data;
	int	id;

	data = (data_t *)arg;
	id = data->pos;
	pthread_mutex_unlock(&(data->mutex));
	printf("id: %d\n", id);
	return (NULL);
}

void	create_philo(data_t *data)
{
	pthread_t	thread[data->philo];
	
	pthread_mutex_init(&(data->mutex), NULL);
	data->pos = 0;
	while (data->pos < data->philo)
	{
		pthread_mutex_lock(&(data->mutex));
		pthread_create(&thread[data->pos], NULL, philo, data);
		data->pos += 1;
	}
	data->pos = 0;
	while (data->pos < data->philo)
	{
		pthread_join(thread[data->pos], NULL);
		data->pos += 1;
	}
}
