/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 16:35:46 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/30 16:35:46 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

static int	reaper(t_data *data, unsigned int res, int i)
{
	if (res > data->time.die)
	{
		message(data, data->philos[i].id, PHILO_DEAD, false);
		return (1);
	}
	return (0);
}

static int	manager(t_data *data)
{
	int				i;
	unsigned int	res;
	unsigned int	tmp;

	while (1)
	{
		i = 0;
		while (i < data->phil_count)
		{
			pthread_mutex_lock(&data->philos[i].eat_lock);
			tmp = data->philos[i].meals;
			res = curr_time(data) - data->philos[i].last_eat;
			if (reaper(data, res, i))
				return (1);
			pthread_mutex_unlock(&data->philos[i].eat_lock);
			if ((int)tmp >= data->min_eat && data->should_eat)
				i++;
			else
				break ;
		}
		if (i == data->phil_count)
			return (0);
	}
}

int			start_threads(t_data *data)
{
	int			i;
	pthread_t	thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->phil_count)
	{
		if (pthread_create(&thread, NULL, simulate, &data->philos[i]))
			error(data, E_THREAD);
		pthread_detach(thread);
		i++;
		usleep(100);
	}
	return (manager(data));
}
