/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:04:14 by acarbajo          #+#    #+#             */
/*   Updated: 2026/01/08 15:34:46 by acarbajo         ###   ########.fr       */
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
	if (parser_argv(argv, data) == -1)
		return (clean_all(data, NULL, NULL));
	table = table_init(data);
	if (!table)
		return (clean_all(data, table, NULL));
	philos = philo_init(data, table);
	create_threads(philos);
	join_threads(philos);
	clean_all(data, table, philos);
	return (0);
}
