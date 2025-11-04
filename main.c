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

void	print_data(t_data *data)
{
	printf("number of philosophers = %i \n", data->n_philos);
	printf("time_to_die  = %i \n", data->time_to_die);
	printf("time_to_eat = %i \n", data->time_to_eat);
	printf("time_to_sleep = %i \n", data->time_to_sleep);
	printf("must_eat = %i \n", data->must_eat);
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

	i = 0;
	while (i < philos->data->n_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
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
	//print_data(data);
	//print_philos(philos, data);

	return (0);

}
