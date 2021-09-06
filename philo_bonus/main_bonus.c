/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:29:00 by pablo             #+#    #+#             */
/*   Updated: 2021/09/03 13:29:40 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 ** Store the parameters given by the user from argv to t_data struct
 ** Check for errors in the given parameters
 **/

static int	store_data(t_data *data, char *argv[])
{
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

/**
 ** Create philos giving them an id
 **/

static int	create_philo(t_data *data)
{
	t_philo	philo;
	pid_t	pid;
	int		count;

	count = 0;
	pid = 1;
	if (init_values(data) == -1)
		return (-1);
	while (count < data->philo && pid > 0)
	{
		pid = fork();
		if (pid > 0)
			data->pid_table[count++] = pid;
		else if (pid == 0)
		{
			philo.id = count + 1;
			philo.data = data;
		}
		else
			return (ph_error("Creación proceso fallida\n"));
	}
	if (pid == 0)
		return (execute_philo(&philo));
	return (wait_for_childs(data->philo, data));
}

/**
 ** Main function -> Philosophers
 **/

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (ph_error("Nº argumentos incorrecto"));
	if (store_data(&data, argv) != 0)
		return (ph_error("Argumentos no validos"));
	if (data.philo == 0)
	{
		printf("\033[33m0 Filosofos = No se come :)\033[39m\n");
		return (0);
	}
	return (create_philo(&data));
}
