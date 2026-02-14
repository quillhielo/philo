/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:35:55 by acarbajo          #+#    #+#             */
/*   Updated: 2026/02/14 18:05:47 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_monitoring(t_philo *philo)
{
	int		state;
	long	current_ms;

	pthread_mutex_lock(&philo->table->meal_mutex);
	current_ms = get_time_stamp() - philo->last_meal;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	if (current_ms > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		philo->table->dead = 1;
		pthread_mutex_unlock(&philo->table->death_mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%li %i died\n",
			(get_time_stamp()) - (philo->table->start_time), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->table->death_mutex);
	state = philo->table->dead;
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (state);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->table->dead == 1)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (0);
}

int	is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	if (philo->data->must_eat != 0
		&& philo->meals_eaten == philo->data->must_eat)
	{
		pthread_mutex_unlock(&philo->table->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->meal_mutex);
	return (0);
}

int	set_full_philos(t_table *table)
{
	pthread_mutex_lock(&philos->table->full_philos_mutex);
	philos->table->full_philos = 1;
	pthread_mutex_unlock(&philos->table->full_philos_mutex);
}

void	*monitoring(void *arg)
{
	t_philo	*philos;
	int		i;
	int		all_ate;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		all_ate = 1;
		while (i < philos->data->n_philos)
		{
			if (!is_full(&philos[i]))
			{
				if (death_monitoring(&philos[i]))
					return (NULL);
				all_ate = 0;
			}
			i++;
		}
		if (philos->data->must_eat != 0 && all_ate)
		{
			return (set_full_philos(philos->table), NULL);
		}
		usleep(1000);
	}
}
