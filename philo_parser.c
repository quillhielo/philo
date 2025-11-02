#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '+')
		i++;
	while(str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

int	atoi_result_checker(long r, long s)
{
	if (r * s < INT_MIN || r * s > INT_MAX)
		return (-1);
	return ((int)(r * s));
}

int	ascii_to_int(const char *str)
{
	size_t		i;
	long		s;
	long		r;
	long		d;

	i = 0;
	s = 1;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	if (!(str[i] >= 48 && str[i] <= 57))
		return (0);
	while (str[i] >= 48 && str[i] <= 57)
	{
		d = str[i] - 48;
		r = r * 10 + d;
		i++;
	}
	return (atoi_result_checker(r, s));
}

int	fill_data(t_data *data, int n, int count)
{
	data->must_eat = -1;
	if (count == 1)
		data->n_philos = n;
	else if (count == 2)
		data->time_to_die = n;
	else if (count == 3)
		data->time_to_eat = n;
	else if (count == 4)
		data->time_to_sleep = n;
	else if (count == 5)
		data->must_eat = n;
	return (0);
}
int	parser_argv(char **argv, t_data *data)
{
	int	i;
	int	n;
	
	i = 1;
	while(argv[i])
	{
		if(!is_digit(argv[i]))
			return (0);
		n = ascii_to_int(argv[i]);
		if (n == -1)
			return (0);
		fill_data(data, n, i);
		i++;
	}
	return (1);
}