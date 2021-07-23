#include "philo.h"

int	ph_error(char *str)
{
	printf("\033[31mError\033[95m\n");
	printf("\033[31m%s\033[95m\n", str);
	return (1);
}

long	ph_atoi(char *str)
{
	long	out;
	long	neg;
	int	count;

	if (str == NULL)
		return (-1);
	count = 0;
	out = 0;
	neg = 1;
	while (str[count] && str[count] == ' ')
		count++;
	if (str[count] == '+' || str[count] == '-')
	{
		if (str[count] == '-')
			neg = -1;
		count++;
	}
	while (str[count])
	{
		if (str[count] < '0' || str[count] > '9')
			return (-1);
		out = (out * 10) + (str[count] - '0');
		count++;
	}
	return (out * neg);
}
