#include "philo.h"

void	philo_action(int time, char *action, t_data *data)
{
	struct timeval	gettime;
	double			time_stamp;

	gettimeofday(&gettime, NULL);
	time_stamp = ((double)gettime.tv_sec * 1000)
		+ ((double)gettime.tv_usec / 1000);
	printf("%ld %d %s\n", (long)time_stamp, data->id, action);
	if (time >= 0)
		ph_sleep(time);
}

void	*execute_philo(void *arg)
{
	struct timeval	start;
	struct timeval	end;
	t_data			*data;
	double			st;
	double			nd;

	data = (t_data *)arg;
	gettimeofday(&start, NULL);
	while (1)
	{
		if (data->fork == 0)
		{
			data->fork = 1;
			philo_action(-1, "has taken a fork", data);
			philo_action(data->eat, "is eating", data);
			gettimeofday(&start, NULL);
			philo_action(data->sleep, "is sleeping", data);
			philo_action(-1, "is thinking", data);
			data->fork = 0;
		}
		gettimeofday(&end, NULL);
		st = ((double)start.tv_sec * 1000) + ((double)start.tv_usec / 1000);
		nd = ((double)end.tv_sec * 1000) + ((double)end.tv_usec / 1000);
		if ((long)(nd - st) > (long)data->death)
		{
			philo_action(-1, "died", data);
			return (NULL);
		}
	}
	return (0);
}

void	create_philo(t_data *data)
{
	data->id = 1;
	data->fork = 0;
	execute_philo(data);
}
