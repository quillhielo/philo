/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:04:14 by acarbajo          #+#    #+#             */
/*   Updated: 2025/10/30 17:31:56 by acarbajo         ###   ########.fr       */
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
	while(str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
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
	return ((int)(r * s));
}
int	fill_data(t_data *data, char *str, int count)
{
	data->must_eat = -1;
	if (count == 1)
		data->n_philos = ascii_to_int(str);
	else if (count == 2)
		data->time_to_die = ascii_to_int(str);
	else if (count == 3)
		data->time_to_eat = ascii_to_int(str);
	else if (count == 4)
		data->time_to_sleep = ascii_to_int(str);
	else if (count == 5)
		data->must_eat = ascii_to_int(str);
	return (0);
}
int	parser_argv(char **argv, t_data *data)
{
	int	i;
	
	i = 1;
	while(argv[i])
	{
		if(!is_digit(argv[i]))
		{
			//clean_data(data);
			return (0);
		}
		fill_data(data, argv[i], i);
		i++;
	}
	return (1);
}
void	print_data(t_data *data)
{
	printf("number of philosophers = %i \n", data->n_philos);
	printf("time_to_die  = %i \n", data->time_to_die);
	printf("time_to_eat = %i \n", data->time_to_eat);
	printf("time_to_sleep = %i \n", data->time_to_sleep);
	printf("must_eat = %i \n", data->must_eat);
}
int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (argc != 5 && argc != 6)
		return (0);
	data = malloc(sizeof(t_data *));
	if(!parser_argv(argv, data))
		return (0);
	print_data(data);
	return (0);

}