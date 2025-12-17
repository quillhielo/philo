/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:46:50 by acarbajo          #+#    #+#             */
/*   Updated: 2025/12/17 20:47:44 by acarbajo         ###   ########.fr       */
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
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
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

void	*monitoring(void *arg)
{
	t_philo	*philos;
	int		i;
	int		time_now;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos->data->n_philos)
		{
			pthread_mutex_lock(&philos[i].table->death_mutex);
			time_now = get_time_stamp();
			if (philos[i].table->dead == 1)
			{
				pthread_mutex_unlock(&philos[i].table->death_mutex);
				return (NULL);
			}
			if (time_now - philos[i].last_meal >= philos->data->time_to_die)
			{
				philos[i].table->dead = 1;
				print_log(&philos[i], "died");
				pthread_mutex_unlock(&philos[i].table->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].table->death_mutex);
			i++;
		}
		usleep(500);
	}
}
