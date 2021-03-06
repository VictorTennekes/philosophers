/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 14:39:26 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/27 14:39:26 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

static void		take_forks(t_philo *philo, pthread_mutex_t *forks, int *set)
{
	pthread_mutex_lock(&forks[set[LEFT]]);
	message(philo->data, philo->id, PHILO_FORK, true);
	pthread_mutex_lock(&forks[set[RIGHT]]);
	message(philo->data, philo->id, PHILO_FORK, true);
	pthread_mutex_lock(&philo->eat_lock);
	message(philo->data, philo->id, PHILO_EAT, true);
	philo->meals++;
	philo->last_eat = curr_time(philo->data);
	pthread_mutex_unlock(&philo->eat_lock);
}

static void		drop_forks(pthread_mutex_t *forks, int *set)
{
	pthread_mutex_unlock(&forks[set[LEFT]]);
	pthread_mutex_unlock(&forks[set[RIGHT]]);
}

void			*simulate(void *arg)
{
	t_philo *philo;
	int		forks[2];

	philo = arg;
	forks[LEFT] = philo->id - 1;
	forks[RIGHT] = philo->id != philo->data->phil_count ? philo->id : 0;
	while (1)
	{
		message(philo->data, philo->id, PHILO_THINK, true);
		take_forks(philo, philo->data->forks, forks);
		usleep(philo->data->time.eat * 1000);
		drop_forks(philo->data->forks, forks);
		message(philo->data, philo->id, PHILO_SLEEP, true);
		usleep(philo->data->time.sleep * 1000);
	}
	return (NULL);
}
