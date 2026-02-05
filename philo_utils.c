/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:04:14 by acarbajo          #+#    #+#             */
/*   Updated: 2026/02/05 22:12:29 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	if (is_dead(philo))
		return ;
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
	pthread_mutex_lock(&philos->table->start_time_mutex);
	philos->table->start_time = get_time_stamp();
	pthread_mutex_unlock(&philos->table->start_time_mutex);
	pthread_mutex_lock(&philos->table->full_table_mutex);
	philos->table->full_table = 1;
	pthread_mutex_unlock(&philos->table->full_table_mutex);
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
