/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:58:08 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/30 16:51:21 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_all	*ft_init_all(t_all *a)
{
	a->thread_philo = ft_malloc(&a->gc, sizeof(pthread_t) * a->nb_philo);
	return (a);
}

t_philo	*ft_search_philo(t_philo *philo, int number)
{
	t_philo	*elem;

	elem = philo;
	while (elem)
	{
		if (elem->number == number)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

t_philo	*ft_create_list(t_all *a, t_philo *philo)
{
	int		i;
	int		prev;
	t_philo	*elem;

	i = 0;
	prev = a->nb_philo;
	while (++i <= a->nb_philo)
		ft_philoadd_back(&philo, ft_new_philo(i, a));
	elem = ft_search_philo(philo, a->nb_philo);
	elem->next = philo;
	i = 1;
	elem = philo;
	ft_search_philo(philo, i)->prev = ft_search_philo(philo, prev--);
	while (++i <= a->nb_philo)
		ft_search_philo(philo, i)->prev = ft_search_philo(philo, i - 1);
	return (philo);
}

int	ft_check_err_and_parse(int nb_args, char **args, t_all *a, t_philo **philo)
{
	if (nb_args < 5 || nb_args > 6)
		return (1);
	if (!ft_is_digit(args[1]) || !ft_is_digit(args[2]) || \
	!ft_is_digit(args[3]) || !ft_is_digit(args[4]))
		return (1);
	a->nb_philo = ft_atoi(args[1]);
	a->time_die = ft_atoi(args[2]);
	a->time_eat = ft_atoi(args[3]);
	a->time_sleep = ft_atoi(args[4]);
	if (a->nb_philo < 1 || a->time_die < 1 || a->time_eat < 1 || \
	a->time_sleep < 1)
		return (1);
	if (nb_args == 6)
	{
		if (!ft_is_digit(args[5]))
			return (1);
		a->nb_time_eat = ft_atoi(args[5]);
		if (a->nb_time_eat < 1)
			return (1);
	}
	*philo = ft_create_list(a, *philo);
	a = ft_init_all(a);
	return (0);
}
