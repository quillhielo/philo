#include "philo.h"

t_philo fill_philos(t_table *table, int id, t_data *data)
{
    t_philo philo;

    philo.id = id + 1;
    philo.table = table;
    philo.data = data;
    philo.thread = 0;
    philo.left_fork = id;
    philo.right_fork = (id + 1) % data->n_philos;
    return (philo);
}

t_philo *philo_init(t_data *data, t_table *table)
{
    int id;
    t_philo *philos;

    id = 0;
    philos =(t_philo*)malloc(sizeof(t_philo) * data->n_philos);
    if (!philos)
        return (0);
    
    while (id < data->n_philos)
    {
        philos[id] = fill_philos(table, id, data);
        id++;
    }
    return (philos);
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    print_log(philo, "is thinking");
    pthread_mutex_lock(&philo->table->fork[philo->left_fork]);
    print_log(philo, "has taken a fork");
    pthread_mutex_lock(&philo->table->fork[philo->right_fork]);
    print_log(philo, "has taken a fork");
    print_log(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->table->fork[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->fork[philo->right_fork]);
    print_log(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
    return (philo);
}