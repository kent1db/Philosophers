/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 21:49:33 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/30 16:54:06 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_and_free(t_all *a, t_list **lst)
{
	int		i;
	t_list	*next;

	i = 0;
	while (i < a->nb_philo)
	{
		pthread_mutex_destroy(&a->forks[i]);
		pthread_detach(a->thread_philo[i++]);
	}
	if (*lst == NULL)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = next;
	}
}

t_philo	*ft_new_philo(int number, t_all *a)
{
	t_philo	*elem;

	elem = ft_malloc(&a->gc, sizeof(t_philo));
	if (!elem)
		return (NULL);
	elem->number = number;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	ft_philoadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*last;

	last = ft_lstlast(*alst);
	if (last != NULL)
		last->next = new;
	else
		*alst = new;
}

void	*ft_malloc(t_list **gc, int size)
{
	void	*malloc_ptr;

	malloc_ptr = malloc(size);
	if (!malloc_ptr)
		return (NULL);
	ft_lstadd_front(gc, ft_lstnew(malloc_ptr));
	return (malloc_ptr);
}

int	ft_init_struct(t_all *a, t_philo *philo)
{
	int		i;
	int		error;
	t_philo	*elem;

	i = 0;
	elem = philo;
	a->forks = ft_malloc(&a->gc, sizeof(pthread_mutex_t) * a->nb_philo);
	error = pthread_mutex_init(&a->print, NULL);
	if (error)
		return (error);
	while (i < a->nb_philo)
	{
		error = pthread_mutex_init(&a->forks[i], NULL);
		elem->a = a;
		elem->alive = 1;
		elem->last_meal = 0;
		elem->nb_eat = 0;
		elem = elem->next;
		i++;
	}
	return (error);
}
