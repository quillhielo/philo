*This project has been created as part of the 42 curriculum by acarbajo.*

# Philosophers

## Description

This project is a simulation of the Dining Philosophers problem, a classical synchronization problem in computer science.

The objective is to manage multiple threads sharing common resources while avoiding concurrency issues such as deadlocks and starvation.

In this implementation:

- Each philosopher is represented by a thread.
- Each fork is represented by a mutex.
- Philosophers alternate between thinking, eating, and sleeping.
- A monitoring mechanism ensures that a philosopher dies if they do not eat within the given time limit.

The program respects the timing constraints provided as arguments and ensures proper synchronization of shared resources.

---

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate the executable:

```bash
philo
```

### Execution

To run the simulation, use the following command format:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

- number_of_philosophers: number of philosophers sitting at the table.

- time_to_die (in milliseconds): maximum time a philosopher can go without eating before dying.

- time_to_eat (in milliseconds): time a philosopher spends eating.

- time_to_sleep (in milliseconds): time a philosopher spends sleeping.

- number_of_times_each_philosopher_must_eat (optional): if provided, the simulation stops once every philosopher has eaten this number of times.
If not provided, the simulation stops when a philosopher dies.

### Example

```bash
./philo 5 800 200 200 7
```

## Resources

- [Wikipedia - Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

- [IBM Documentation - pthread_mutex_lock, pthread_mutex_trylock, pthread_mutex_unlock](https://www.ibm.com/docs/es/aix/7.3.0?topic=p-pthread-mutex-lock-pthread-mutex-trylock-pthread-mutex-unlock-subroutine)

- [Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/)

- Discussions and knowledge sharing with fellow students at 42 Campus, which helped deepen understanding of concurrency and synchronization.

### Use of AI

AI tools were used to assist in debugging and improving understanding of synchronization concepts, as well as refining the README file.

All implementation logic and design decisions were developed and understood by the author.