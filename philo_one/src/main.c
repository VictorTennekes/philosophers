/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 14:32:26 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/26 14:32:26 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <string.h>
#include <stdio.h>
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
	int i;
	unsigned int res;
	unsigned int philo[2];

	while (1)
	{
		i = 0;
		while (i < data->phil_count)
		{
			pthread_mutex_lock(&data->philos[i].eat_lock);
			philo[0] = data->philos[i].last_eat;
			philo[1] = data->philos[i].meals;
			pthread_mutex_unlock(&data->philos[i].eat_lock);
			res = curr_time(data) - philo[0];
			if (reaper(data, res, i))
				return (1);
			if ((int)philo[1] == data->min_eat)
				i++;
			else
				break ;
		}
		if (i == data->phil_count)
			return (0);
	}
}

static int start_threads(t_data *data)
{
	int i;
	pthread_t thread;

	i = 0;
	while (i < data->phil_count)
	{
		init_philo(data, &data->philos[i], i);
		if (pthread_create(&thread, NULL, simulate, &data->philos[i]))
			error(data, E_THREAD);
		pthread_detach(thread);
		i++;
		usleep(100);
	}
	return (manager(data));
}

int main(int ac, char **av)
{
	t_data *data;
	int i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		error(data, E_MALLOC "data");
	memset(data, 0, sizeof(t_data));
	data->start_time = get_time();
	parse_input(data, ac, av);
	data->philos = malloc(sizeof(t_philo) * data->phil_count);
	while (i < data->phil_count)
	{
		pthread_mutex_init(&data->philos[i].eat_lock, NULL);
		i++;
	}
	if (!data->philos)
		error(data, E_MALLOC "philosophers");
	start_threads(data);
}