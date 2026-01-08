/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:39:09 by acarbajo          #+#    #+#             */
/*   Updated: 2025/12/22 14:35:04 by acarbajo         ###   ########.fr       */
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
	long	n_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
}	t_data;

typedef struct s_table
{
	long			n_philos;
	int				dead;
	int				all_ate;
	int				full_table;
	pthread_t		monitor_thread;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*fork;
	long			start_time;
}	t_table;

typedef struct s_philo
{
	int			id;
	int			has_eaten;
	t_table		*table;
	pthread_t	thread;
	int			left_fork;
	int			right_fork;
	long		last_meal;
	long		meals_eaten;
	t_data		*data;
}	t_philo;

int		is_digit(char *str);
long	atlong(const char *str);
int		fill_data(t_data *data, int n, int count);
int		parser_argv(char **argv, t_data *data);
t_philo	fill_philos(t_table *table, int id, t_data *data);
int		eat(t_philo *philo);
void	*routine(void *arg);
void	*monitoring(void *arg);
t_table	*table_init(t_data *data);
t_philo	*philo_init(t_data *data, t_table *table);
void	print_log(t_philo *philo, char *str);
long	get_time_stamp(void);
void	active_sleep(long	duration_ms,t_philo *philo);
int		is_dead(t_philo *philo);
void	create_threads(t_philo *philos);
void	join_threads(t_philo *philos);
int		clean_data(t_data *data);
int		clean_table(t_table *table);
int		clean_philos(t_philo *philos);
int		clean_all(t_data *data, t_table *table, t_philo *philos);
int 	death_monitoring(t_philo *philo);

#endif
