/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:10:53 by bmicheal          #+#    #+#             */
/*   Updated: 2021/02/08 17:32:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define YELLOW	"\033[1;33m"
# define WHITE	"\033[1;37m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define ARR	"🤬"

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdio.h>

struct s_stuct;

typedef struct		s_phil
{
	struct s_struct	*all;
	int				id;
	int				left_hand;
	int				right_hand;
	unsigned long	t_last_dinner;
	unsigned long	t_to_live;
	int				dop_start;
	int				dop_end;
	pthread_t		t;
	sem_t			*is_eating;
	int				eat;
}					t_phil;

typedef struct		s_struct
{
	t_phil			*p;
	int				is_dead;
	int				phils;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_times;
	int				e_t_all;
	unsigned long	time_start;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*dead;
}					t_struct;

int					ft_atoi(const char *str);
unsigned long		now(void);
void				my_sleep(int time);
void				printf_pro(t_phil *phil, char *str);
void				*warden(void *ptr);

#endif
