/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 14:37:42 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/26 14:37:42 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

void	message(t_data *data, int id, char *msg, bool unlock)
{
	unsigned int	time;
	char			*time_str;
	char			*id_str;

	time = curr_time(data);
	time_str = ultoa(time);
	if (!time_str)
		error(data, E_MALLOC "time_string");
	id_str = ultoa(id);
	if (!id_str)
	{
		free(time_str);
		error(data, E_MALLOC "id_string");
	}
	pthread_mutex_lock(&data->write_lock);
	ft_putstr_fd(time_str, 1);
	(void)write(1, " ", 1);
	ft_putstr_fd(id_str, 1);
	ft_putstr_fd(msg, 1);
	if (unlock)
		pthread_mutex_unlock(&data->write_lock);
	free(time_str);
	free(id_str);
}

int		ft_putstr_fd(char *str, int fd)
{
	int len;
	int tot;

	len = 0;
	tot = 0;
	while (str[len] != '\0')
		len += 1;
	while (tot != len)
		tot += write(fd, str + tot, len - tot);
	return (tot);
}

bool	is_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (true);
		i++;
	}
	return (false);
}

char	*ultoa(unsigned long number)
{
	char			*res;
	int				size;
	unsigned long	num;

	num = number;
	size = 1;
	while (num >= 10)
	{
		num /= 10;
		size++;
	}
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	res[size] = '\0';
	while (size)
	{
		res[size - 1] = (number % 10) + '0';
		number /= 10;
		size--;
	}
	return (res);
}

int		ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = *str == '-' ? -1 : 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * (int)res);
}
