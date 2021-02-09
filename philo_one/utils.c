/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:44:30 by bmicheal          #+#    #+#             */
/*   Updated: 2021/02/09 09:31:20 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				ft_atoi(const char *str)
{
	long	neg;
	long	nbr;

	neg = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v' ||
		*str == '\f' || *str == '\r' || *str == '\n')
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return ((int)(nbr * neg));
}

unsigned long	now(void)
{
	struct timeval	t_time;

	gettimeofday(&t_time, NULL);
	return ((t_time.tv_sec * (unsigned long)1000) + (t_time.tv_usec / 1000));
}

void			my_sleep(int time, t_struct *all)
{
	unsigned long end;

	end = now() + time;
	while (now() < end && !all->is_dead)
		usleep(time);
}

void			printf_pro(t_phil *p, char *str)
{
	if (!p->all->is_dead && p->all->e_t_all != 0)
	{
		pthread_mutex_lock(&p->all->print);
		if (!p->all->is_dead && p->all->e_t_all != 0)
			printf("%lu %d %s\n", (now() - p->all->time_start),
			p->id, str);
		pthread_mutex_unlock(&p->all->print);
	}
}

void			*warden(void *ptr)
{
	t_phil *p;

	p = (t_phil *)ptr;
	while (!p->all->is_dead)
	{
		usleep(100);
		pthread_mutex_lock(&p->is_eating);
		if (now() - p->t_last_dinner > (unsigned int)p->all->t_die &&
		!p->all->is_dead)
		{
			p->all->is_dead = 1;
			pthread_mutex_unlock(&p->is_eating);
			pthread_mutex_lock(&p->all->dead);
			printf("%lu %d %sdied\n", (now() - p->all->time_start), p->id, RED);
			return (NULL);
		}
		else if (!p->all->is_dead && p->dop_end != -1 && p->dop_start
		>= p->dop_end)
			return (NULL);
		pthread_mutex_unlock(&p->is_eating);
	}
	return (NULL);
}
