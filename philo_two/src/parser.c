/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 12:21:33 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/27 12:21:33 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		init_philo(t_data *data, t_philo *philo, int id)
{
	philo->id = id + 1;
	philo->last_eat = 0;
	philo->meals = 0;
	philo->data = data;
}

static bool	init_data(t_data *data, bool eat_min, char **av)
{
	data->phil_count = ft_atoi(av[1]);
	data->time.die = ft_atoi(av[2]);
	data->time.eat = ft_atoi(av[3]);
	data->time.sleep = ft_atoi(av[4]);
	if (eat_min)
		data->min_eat = ft_atoi(av[5]);
	data->should_eat = eat_min;
	if (data->phil_count < 2 || data->phil_count > 200)
		return (true);
	if (data->time.die < 60 || data->time.eat < 60 || data->time.sleep < 60)
		return (true);
	if (data->min_eat && data->min_eat <= 0)
		return (true);
	return (false);
}

void		parse_input(t_data *data, int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 5 || ac > 6)
		error(data, E_ARGC);
	while (i < ac)
	{
		if (is_number(av[i]))
			error(data, E_INPUT);
		i++;
	}
	i = 0;
	if (init_data(data, (ac == 6), av))
		error(data, E_INPUT);
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 666, data->phil_count);
	if (!data->forks)
		error(data, E_MALLOC "forks");
	sem_unlink("write_lock");
	data->write_lock = sem_open("write_lock", O_CREAT, 666, 1);
}
