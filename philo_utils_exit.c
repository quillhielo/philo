/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:46:14 by acarbajo          #+#    #+#             */
/*   Updated: 2025/12/17 21:10:19 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_data(t_data *data)
{
	free(data);
	return (0);
}

int	clean_table(t_table *table)
{
	long	i;

	if (!table)
		return (1);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	free(table->fork);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	free(table);
	return (0);
}
int	clean_philos(t_philo *philos)
{
	if (philos->table)
		clean_table(philos->table);
	if (philos->data)
		clean_data(philos->data);
	free(philos);
	return (0);
}
int	clean_all(t_data *data, t_table *table, t_philo *philos)
{
	if (philos)
	{
		clean_philos(philos);
	}
	else
	{
		if (table)
			clean_table(table);
		if (data)
			clean_data(data);
	}
	return (0);
}

