/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:04:14 by acarbajo          #+#    #+#             */
/*   Updated: 2025/10/30 17:31:56 by acarbajo         ###   ########.fr       */
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
void	print_philos(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	while(i < data->n_philos)
	{
		printf("id: %i\n", philos[i]->id);
		printf("has eaten: %i\n", philos[i]->has_eaten);
		i++;
	}
}
int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo **philos;

	
	if (argc != 5 && argc != 6)
		return (0);
	data = malloc(sizeof(t_data *));
	if(!parser_argv(argv, data))
	{
		free(data);
		return (0);
	}
	philos = philo_init(data);
	print_data(data);
	print_philos(philos, data);
	return (0);

}
