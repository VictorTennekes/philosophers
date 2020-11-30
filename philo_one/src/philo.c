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
#include <stdio.h>
#include <unistd.h>

static void	take_forks(t_philo *philo, pthread_mutex_t *forks, int *set)
{
	pthread_mutex_lock(&forks[set[LEFT]]);
	message(philo->data, philo->id, PHILO_FORK, true);
	pthread_mutex_lock(&forks[set[RIGHT]]);
	message(philo->data, philo->id, PHILO_EAT, true);
	// lock
	philo->meals++;
	philo->last_eat = curr_time(philo->data);
	// unlock
}

static void	drop_forks(pthread_mutex_t *forks, int *set)
{
	pthread_mutex_unlock(&forks[set[LEFT]]);
	pthread_mutex_unlock(&forks[set[RIGHT]]);
}

void		init_philo(t_data *data, t_philo *philo, int id)
{
	philo->id = id + 1;
	philo->last_eat = 0;
	philo->meals = 0;
	philo->data = data;
}

void 		*simulate(void *arg)
{
	t_philo *philo;
	int		forks[2];

	philo = arg;
	forks[LEFT] = philo->id - 1;
	forks[RIGHT] = philo->id != philo->data->phil_count ? philo->id : 0;
	#ifdef DEBUG
		dprintf(2 ,"philo[%i]->forks[%i, %i]\n", philo->id, forks[LEFT], forks[RIGHT]);
	#endif
	while (1)
	{
		message(philo->data, philo->id, PHILO_THINK, true);
		take_forks(philo, philo->data->forks, forks);
		usleep(philo->data->time.eat * 1000);
		drop_forks(philo->data->forks, forks);
		message(philo->data, philo->id, PHILO_SLEEP, true);
		usleep(philo->data->time.sleep * 1000);
	}
	return(NULL);
}