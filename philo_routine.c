/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:53:42 by acarbajo          #+#    #+#             */
/*   Updated: 2025/12/22 17:21:10 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->right_fork]);
	print_log(philo, "has taken a fork");
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->table->fork[philo->right_fork]);
		return (0);
	}
	if (philo->left_fork == philo->right_fork)
	{
		active_sleep(philo->data->time_to_die, philo);
		pthread_mutex_unlock(&philo->table->fork[philo->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->table->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal = get_time_stamp();
	philo->meals_eaten ++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->table->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->table->fork[philo->right_fork]);
		return (0);
	}
	print_log(philo, "has taken a fork");
	print_log(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->table->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->fork[philo->right_fork]);
	return (1);
}
void	active_sleep(long	duration_ms,t_philo *philo)
{
	long	ms_init;
	
	ms_init = get_time_stamp();
	while (!is_dead(philo) && get_time_stamp() - ms_init < duration_ms)
		usleep(500);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!philo->table->full_table)
		usleep(500);
	philo->last_meal = philo->table->start_time;
	if (philo->id % 2 == 0)
			usleep(2000);
	while (!is_dead(philo) && !philo->table->all_ate)
	{
		print_log(philo, "is thinking");
		if (is_dead(philo) || philo->table->all_ate)
			return (0);		
		if (!eat(philo))
			break ;
		if (is_dead(philo) || philo->table->all_ate)
			return (0);
		print_log(philo, "is sleeping");
		active_sleep(philo->data->time_to_sleep, philo);
	}
	return (NULL);
}
