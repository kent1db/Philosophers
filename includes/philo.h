/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 19:09:54 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/30 18:16:41 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "color.h"

typedef enum e_enum_philo
{
	dead,
	sleeping,
	thinking,
	eating
}				t_enum_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_all
{
	int				beg_time;
	int				nb_philo;
	int				i;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_time_eat;
	int				error;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	time;
	pthread_t		*thread_philo;
	t_list			*gc;
}				t_all;

typedef struct s_philo
{
	int				number;
	int				alive;
	int				last_meal;
	int				nb_eat;
	pthread_mutex_t	lock;
	t_all			*a;
	struct s_philo	*prev;
	struct s_philo	*next;
}					t_philo;

/***** LIST *****/
void	*ft_malloc(t_list **gc, int size);
t_philo	*ft_new_philo(int number, t_all *a);
void	ft_philoadd_back(t_philo **alst, t_philo *new);
int		ft_init_struct(t_all *a, t_philo *philo);
void	ft_destroy_and_free(t_all *a, t_list **lst);

/***** LIBFT *****/
int		ft_atoi(const char *str);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_is_digit(char *str);

/***** ERROR *****/
t_philo	*ft_search_philo(t_philo *philo, int number);
int		ft_check_err_and_parse(int nb_args, char **args, t_all *a,
			t_philo **philo);

/***** PRINT *****/
int		ft_time(t_all *a);
void	ft_print_fork(t_philo *philo);
void	ft_print_eat(t_philo *philo);
void	ft_print_sleep(t_philo *philo);
void	ft_print_think(t_philo *philo);

/***** UTILS *****/
int		ft_all_eat_at_time(t_philo *philo, t_all *a);
int		ft_is_alive(t_all *a, t_philo *philo);
t_all	*ft_init_var(struct timeval time);
int		ft_all_eat(t_philo *philo, t_all *a);

#endif
