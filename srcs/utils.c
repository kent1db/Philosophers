/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:08:05 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/30 18:53:19 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_all_eat(t_philo *philo, t_all *a)
{
	t_philo	*elem;
	int		i;

	i = 0;
	elem = philo;
	while (i < a->nb_philo)
	{
		if (elem->nb_eat < a->nb_time_eat)
			return (0);
		i++;
		elem = elem->next;
	}
	return (1);
}

int	ft_all_eat_at_time(t_philo *philo, t_all *a)
{
	struct timeval	time;
	int				res;
	t_philo			*elem;
	int				i;

	elem = philo;
	i = 0;
	usleep(3000);
	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000 + time.tv_usec / 1000) - a->beg_time;
	while (i < a->nb_philo)
	{
		pthread_mutex_lock(&elem->lock);
		if (res - elem->last_meal > a->time_die)
		{
			pthread_mutex_lock(&a->print);
			printf(YEL "%d"RESET" %d died\n", ft_time(a), elem->number);
			return (0);
		}
		pthread_mutex_unlock(&elem->lock);
		elem = elem->next;
		i++;
	}
	return (1);
}

t_all	*ft_init_var(struct timeval time)
{
	t_all	*a;

	a = malloc(sizeof(t_all));
	a->gc = NULL;
	ft_lstadd_front(&a->gc, ft_lstnew(a));
	a->beg_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	a->nb_philo = -1;
	a->time_die = -1;
	a->time_eat = -1;
	a->time_sleep = -1;
	a->nb_time_eat = -1;
	return (a);
}
