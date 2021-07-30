/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:06:46 by pablo             #+#    #+#             */
/*   Updated: 2021/07/27 17:16:13 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	data->status = 0;
	data->waiter = 1;
	if (argv[5] != NULL)
		data->times = (int)ph_atoi(argv[5]);
	return (0);
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
		return (ph_error("Argumentos no válidos"));
	return (create_philo(&data));
}
