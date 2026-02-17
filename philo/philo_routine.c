/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:53:42 by acarbajo          #+#    #+#             */
/*   Updated: 2026/02/14 17:27:07 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->first_fork]);
	print_log(philo, "has taken a fork");
	if (is_dead(philo))
		return (pthread_mutex_unlock
			(&philo->table->fork[philo->first_fork]), 0);
	if (philo->first_fork == philo->second_fork)
	{
		active_sleep(philo->data->time_to_die, philo);
		pthread_mutex_unlock(&philo->table->fork[philo->first_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->table->fork[philo->second_fork]);
	print_log(philo, "has taken a fork");
	return (1);
}

int	eat(t_philo *philo)
{
	if (is_full_philos(philo))
		return (0);
	if (!take_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal = get_time_stamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->table->fork[philo->second_fork]);
		pthread_mutex_unlock(&philo->table->fork[philo->first_fork]);
		return (0);
	}
	print_log(philo, "is eating");
	active_sleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->table->fork[philo->second_fork]);
	pthread_mutex_unlock(&philo->table->fork[philo->first_fork]);
	return (1);
}

void	active_sleep(long duration_ms, t_philo *philo)
{
	long	ms_init;

	ms_init = get_time_stamp();
	while (!is_dead(philo) && get_time_stamp() - ms_init < duration_ms)
		usleep(500);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		active_sleep(100, philo);
	while (!is_dead(philo) && !is_full_philos(philo))
	{
		if (!eat(philo))
			break ;
		if (is_full(philo))
			return (0);
		print_log(philo, "is sleeping");
		active_sleep(philo->data->time_to_sleep, philo);
		print_log(philo, "is thinking");
	}
	return (NULL);
}
