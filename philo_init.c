#include "philo.h"

t_philo *fill_philos(t_data *data, int id)
{
    t_philo *philo;

    philo =(t_philo*)malloc(sizeof(t_philo));
    if (!philo)
        return (NULL);
    philo->id = id + 1;
    philo->has_eaten = 0;
    philo->data = data;
    return (philo);
}

t_philo **philo_init(t_data *data)
{
    int id;
    t_philo **philos;

    id = 0;
    philos =(t_philo**)malloc(sizeof(t_philo*) * data->n_philos);
    if (!philos)
        return (0);
    
    while (id <= data->n_philos)
    {
        philos[id]= fill_philos(data, id);
        id++;
    }
    return (philos);
}