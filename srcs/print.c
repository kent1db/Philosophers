/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:13:40 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/30 19:18:07 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time(t_all *a)
{
	struct timeval	time;
	int				res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000 + time.tv_usec / 1000) - a->beg_time;
	return (res);
}

void	ft_print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->a->print);
	printf(YEL "%d" RESET" %d" BLU " has taken a fork\n" RESET,
		ft_time(philo->a), philo->number);
	pthread_mutex_unlock(&philo->a->print);
}

void	ft_print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = ft_time(philo->a);
	pthread_mutex_unlock(&philo->lock);
	philo->nb_eat += 1;
	pthread_mutex_lock(&philo->a->print);
	printf(YEL "%d" RESET" %d" GRN " is eating\n" RESET,
		ft_time(philo->a), philo->number);
	pthread_mutex_unlock(&philo->a->print);
	usleep(philo->a->time_eat * 1000);
}

void	ft_print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->a->print);
	printf(YEL "%d" RESET" %d" MAG " is sleeping\n" RESET,
		ft_time(philo->a), philo->number);
	pthread_mutex_unlock(&philo->a->print);
	usleep(philo->a->time_sleep * 1000);
}

void	ft_print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->a->print);
	printf(YEL "%d" RESET" %d" CYN " is thinking\n" RESET,
		ft_time(philo->a), philo->number);
	pthread_mutex_unlock(&philo->a->print);
}
