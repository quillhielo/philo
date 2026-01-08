/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:50:45 by acarbajo          #+#    #+#             */
/*   Updated: 2025/12/17 20:51:28 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i = 0;

	if (!str[i])
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

long	atlong(const char *str)
{
	size_t	i = 0;
	long	r = 0;
	long	d;

	if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		d = str[i] - '0';
		if (r > (LONG_MAX - d) / 10) 
			return (-1);
		r = r * 10 + d;
		i++;
	}
	if (r == 0)
		return (-1);
	return (r);
}

int	fill_data(t_data *data, int n, int count)
{
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

	data->must_eat = 0;
	i = 1;
	while (argv[i])
	{
		if (is_digit(argv[i]) == -1)
			return (-1);
		n = atlong(argv[i]);
		if (n == -1)
			return (-1);
		fill_data(data, n, i);
		if ((i == 1 && data->n_philos <= 0) ||
		    (i == 2 && data->time_to_die <= 0) ||
		    (i == 3 && data->time_to_eat <= 0) ||
		    (i == 4 && data->time_to_sleep <= 0))
			return (-1);
		i++;
	}
	return (0);
}
