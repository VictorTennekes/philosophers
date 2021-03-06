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

#include "philo_two.h"
#include <string.h>

void	error(t_data *data, char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(data);
	exit(1);
}

int		main(int ac, char **av)
{
	t_data	*data;
	char	*id;
	int		i;

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
		id = ultoa(i);
		sem_unlink(id);
		data->philos[i].eat_lock = sem_open(id, O_CREAT, 666, 1);
		free(id);
		init_philo(data, &data->philos[i], i);
		i++;
	}
	if (!data->philos)
		error(data, E_MALLOC "philosophers");
	return(start_threads(data));
}
