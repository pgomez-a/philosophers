#include "philo.h"

static int	store_data(data_t *data, char *argv[])
{
	int	num;

	if (ph_atoi(argv[1]) < 0 || ph_atoi(argv[1]) > INT_MAX)
		return (-1);
	if (ph_atoi(argv[2]) < 0 || ph_atoi(argv[2]) > INT_MAX)
		return (-1);
	if (ph_atoi(argv[3]) < 0 || ph_atoi(argv[3]) > INT_MAX)
		return (-1);
	if (ph_atoi(argv[4]) < 0 || ph_atoi(argv[4]) > INT_MAX)
		return (-1);
	if (argv[5] != NULL && (ph_atoi(argv[5]) < 0 || ph_atoi(argv[5]) > INT_MAX))
		return (-1);
	data->philo = (int)ph_atoi(argv[1]);
	data->death = (int)ph_atoi(argv[2]);
	data->eat = (int)ph_atoi(argv[3]);
	data->sleep = (int)ph_atoi(argv[4]);
	data->times = -1;
	if (argv[5] != NULL)
		data->times = (int)ph_atoi(argv[5]);
	return (0);
}

void	read_data(data_t *data)
{
	printf("philo:  %d\n", data->philo);
	printf("death:  %d\n", data->death);
	printf("eat:    %d\n", data->eat);
	printf("sleep:  %d\n", data->sleep);
	printf("times:  %d\n", data->times);
}

int	main(int argc, char *argv[])
{
	data_t	data;

	if (argc != 5 && argc != 6)
		return (ph_error("Nº argumentos incorrecto"));
	if (store_data(&data, argv) != 0)
		return (ph_error("Argumentos no válidos"));
	create_philo(&data);
	return (0);
}
