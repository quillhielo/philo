/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:04:14 by acarbajo          #+#    #+#             */
/*   Updated: 2025/11/04 20:26:40 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
{
	t_philo *philos;
	int	i;
	int	time_now;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos->data->n_philos)
		{
			time_now = get_time_stamp();
			if (time_now - philos[i].last_meal >= philos->data->time_to_die)
			{
				pthread_mutex_lock(&philos[i].table->death_mutex);
				philos[i].table->dead = 1;
				print_log(&philos[i], "died");
				pthread_mutex_unlock(&philos[i].table->death_mutex);
				return (0);
			}
			i++;
		}
	}
}

void	print_data(t_data *data)
{
	printf("number of philosophers = %li \n", data->n_philos);
	printf("time_to_die  = %li \n", data->time_to_die);
	printf("time_to_eat = %li \n", data->time_to_eat);
	printf("time_to_sleep = %li \n", data->time_to_sleep);
	printf("must_eat = %li \n", data->must_eat);
}

void	print_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while(i < data->n_philos)
	{
		printf("id: %i\n", philos[i].id);
		printf("has eaten: %i\n", philos[i].has_eaten);
		i++;
	}
}

t_table	*table_init(t_data *data)
{
	t_table	*table;

	int	i;
	
	i = 0;
	table = malloc(sizeof(t_table));
	if (!table)
		return(0);//limpiar
	table->fork = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	
	while (i < data->n_philos)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
	table->dead = 0;
	return (table);
}

int	get_time_stamp()
{
	int	ms;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}
void	print_log(t_philo *philo, char *str)
{
	int	ms;

	ms = get_time_stamp();
	printf("%i %i %s\n", ms, philo->id, str);
}
void	create_threads(t_philo *philos)
{
	int	i;
	pthread_t	monitor_thread;

	i = 0;
	philos->table->start_time = get_time_stamp();
	while (i < philos->data->n_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitoring, &philos);
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
}



int	main(int argc, char **argv)
{
	t_data	*data;
	t_table	*table;
	t_philo *philos;

	if (argc != 5 && argc != 6)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);//limpiar
	if(!parser_argv(argv, data))
	{
		free(data);
		return (0);
	}
	table = table_init(data);
	philos = philo_init(data, table);
	create_threads(philos);
	monitoring(philos);
	join_threads(philos);
	//print_data(data);
	//print_philos(philos, data);

	return (0);

}
