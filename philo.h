/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:39:09 by acarbajo          #+#    #+#             */
/*   Updated: 2025/10/30 17:32:16 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <string.h> //memset
# include <stdio.h> // printf 
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <pthread.h> // pthread_create, pthread_detach, pthread_join,  pthread_mutex_init, destroy, mutex_lock, mutex_unlock
# include <limits.h> // min_int, max_int

typedef struct s_data
{
	int	n_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_data;

typedef	struct s_philo
{
	int	id;
	int	has_eaten;
	t_data	*data;
} t_philo;

int	is_digit(char *str);
int	atoi_result_checker(long r, long s);
int	ascii_to_int(const char *str);
int	fill_data(t_data *data, int n, int count);
int	parser_argv(char **argv, t_data *data);
t_philo *fill_philos(t_data *data, int id);
t_philo **philo_init(t_data *data);





#endif
