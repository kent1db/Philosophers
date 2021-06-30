/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 19:09:36 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/30 19:24:47 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread_loop(void *arg)
{
	t_philo	*p;

	p = arg;
	while (1)
	{
		if (p->a->nb_time_eat > 0 && p->nb_eat >= p->a->nb_time_eat)
			break ;
		pthread_mutex_lock(&p->a->forks[p->number - 1]);
		ft_print_fork(p);
		pthread_mutex_lock(&p->a->forks[p->next->number - 1]);
		ft_print_fork(p);
		ft_print_eat(p);
		pthread_mutex_unlock(&p->a->forks[p->next->number - 1]);
		pthread_mutex_unlock(&p->a->forks[p->number - 1]);
		ft_print_sleep(p);
		ft_print_think(p);
	}
	return (arg);
}

int	ft_main_loop(t_all *a, t_philo *philo)
{
	int		i;
	int		err;
	t_philo	*elem;

	i = 0;
	elem = philo;
	while (i < a->nb_philo)
	{
		err = pthread_create(&a->thread_philo[i], NULL, &ft_thread_loop, elem);
		elem = elem->next;
		usleep(70);
		i++;
	}
	return (err);
}

int	main(int ac, char **av)
{
	t_all			*a;
	t_philo			*philo;
	struct timeval	time;

	gettimeofday(&time, NULL);
	a = NULL;
	philo = NULL;
	a = ft_init_var(time);
	if (ft_check_err_and_parse(ac, av, a, &philo))
		return (1);
	if (ft_init_struct(a, philo))
		return (1);
	if (ft_main_loop(a, philo))
		return (1);
	while (ft_all_eat_at_time(philo, a))
	{
		if (a->nb_time_eat > 0 && ft_all_eat(philo, a))
			break ;
	}
	ft_destroy_and_free(a, &a->gc);
	return (0);
}
