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
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

int	atlong(const char *str)
{
	size_t	i;
	long	r;
	long	d;

	i = 0;
	r = 0;
	if (!(str[i] >= 48 && str[i] <= 57))
		return (-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		d = str[i] - 48;
		r = r * 10 + d;
		i++;
	}
	return (r);
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
	while (argv[i])
	{
		if (!is_digit(argv[i]))
			return (0);
		n = atlong(argv[i]);
		if (n == -1)
			return (0);
		fill_data(data, n, i);
		i++;
	}
	return (1);
}
