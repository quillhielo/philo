/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:53:42 by acarbajo          #+#    #+#             */
/*   Updated: 2025/12/17 21:55:45 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->table->fork[philo->right_fork]);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->table->fork[philo->left_fork]);
	print_log(philo, "has taken a fork");
	if (is_dead(philo))
		return (0);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->table->fork[philo->left_fork]);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->table->fork[philo->right_fork]);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal = get_time_stamp();
	pthread_mutex_unlock(&philo->table->meal_mutex);
	if (is_dead(philo))
		return (0);
	print_log(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->table->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->fork[philo->right_fork]);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = philo->table->start_time;
	while (philo->table->dead == 0)
	{
		if (is_dead(philo))
			break ;
		print_log(philo, "is thinking");
		if (is_dead(philo))
			break ;
		if (!eat(philo))
			break ;
		print_log(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (philo);
}
