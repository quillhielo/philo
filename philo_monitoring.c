
#include "philo.h"

int death_monitoring(t_philo *philo)
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
		return (1);
	}
	state = philo->table->dead;
	pthread_mutex_unlock(&philo->table->death_mutex);
	pthread_mutex_unlock(&philo->table->meal_mutex);
	return (state);
}

void	*monitoring(void *arg)
{
	t_philo	*philos;
	int		i;
    int     all_ate;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
        all_ate = 1;
		while (i < philos->data->n_philos)
		{
			if (death_monitoring(&philos[i]))
				return (NULL);
			if (philos->data->must_eat != 0)
            {
                pthread_mutex_lock(&philos->table->meal_mutex);
                if (philos[i].meals_eaten < philos->data->must_eat)
                    all_ate = 0;
                pthread_mutex_unlock(&philos->table->meal_mutex);
            }
			i++;
		}
        if (philos->data->must_eat != 0 && all_ate)
        {
            philos->table->all_ate = 1;
            return (NULL);
        }
		usleep(500);
	}
}
