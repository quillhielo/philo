/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:04:14 by acarbajo          #+#    #+#             */
/*   Updated: 2025/12/22 17:31:29 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	state;
	long	current_ms;

	pthread_mutex_lock(&philo->table->death_mutex);
	pthread_mutex_lock(&philo->table->meal_mutex);
	current_ms = get_time_stamp() - philo->last_meal;
	if (current_ms >= philo->data->time_to_die)
	{
		philo->table->dead = 1;
		pthread_mutex_unlock(&philo->table->death_mutex);
		pthread_mutex_unlock(&philo->table->meal_mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%li %i died\n", current_ms, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (1);
	}
	state = philo->table->dead;
	pthread_mutex_unlock(&philo->table->death_mutex);
	pthread_mutex_unlock(&philo->table->meal_mutex);
	return (state);
}

long	get_time_stamp(void)
{
	long			ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	print_log(t_philo *philo, char *str)
{
	int	ms;
	
	if(is_dead(philo))
		return;
	pthread_mutex_lock(&philo->table->print_mutex);
	ms = (get_time_stamp()) - (philo->table->start_time);
	printf("%i %i %s\n", ms, philo->id, str);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	create_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->n_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&philos->table->monitor_thread, NULL, monitoring, philos);
	philos->table->start_time = get_time_stamp();
	philos->table->full_table = 1;
}

void	join_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(philos->table->monitor_thread, NULL);
}
