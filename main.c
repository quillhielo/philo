/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:04:14 by acarbajo          #+#    #+#             */
/*   Updated: 2025/12/22 16:50:04 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_table	*table;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (!parser_argv(argv, data))
		return (clean_data(data));
	table = table_init(data);
	if (!table)
		return (clean_data(data));
	philos = philo_init(data, table);
	create_threads(philos);
	monitoring(philos);
	join_threads(philos);
	clean_table(table);
	return (0);
}

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
