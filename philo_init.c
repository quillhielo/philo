/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:46:50 by acarbajo          #+#    #+#             */
/*   Updated: 2026/01/08 15:31:46 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*table_init(t_data *data)
{
	t_table	*table;
	int		i;

	i = 0;
	table = malloc(sizeof(t_table));
	if (!table)
		return (0);
	table->n_philos = data->n_philos;
	table->fork = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	while (i < data->n_philos)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
	table->dead = 0;
	table->all_ate = 0;
	table->full_table = 0;
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	table->start_time = get_time_stamp();
	return (table);
}

t_philo	fill_philos(t_table *table, int id, t_data *data)
{
	t_philo	philo;

	philo.id = id + 1;
	philo.table = table;
	philo.data = data;
	philo.thread = 0;
	philo.left_fork = id;
	philo.right_fork = (id + 1) % data->n_philos;
	philo.has_eaten = 0;
	philo.last_meal = table->start_time;
	philo.meals_eaten = 0;
	return (philo);
}

t_philo	*philo_init(t_data *data, t_table *table)
{
	int		id;
	t_philo	*philos;

	id = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	if (!philos)
		return (0);
	while (id < data->n_philos)
	{
		philos[id] = fill_philos(table, id, data);
		id++;
	}
	return (philos);
}
