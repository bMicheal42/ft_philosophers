/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:28:16 by bmicheal          #+#    #+#             */
/*   Updated: 2021/02/09 09:37:32 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dinner(t_phil *p)
{
	sem_wait(p->all->forks);
	printf_pro(p, "has taken a fork");
	sem_wait(p->all->forks);
	printf_pro(p, "has taken a fork");
	sem_wait(p->is_eating);
	p->t_last_dinner = now();
	printf_pro(p, "is eating");
	p->dop_start++;
	p->all->e_t_all -= p->all->e_t_all > 0 ? 1 : 0;
	my_sleep(p->all->t_eat);
	sem_post(p->is_eating);
	sem_post(p->all->forks);
	sem_post(p->all->forks);
	printf_pro(p, "is sleeping");
	my_sleep(p->all->t_sleep);
	printf_pro(p, "is thinking");
}

void	*life(void *ptr)
{
	t_phil		*p;
	pthread_t	t_check;

	p = (t_phil*)ptr;
	p->t_last_dinner = now();
	if (pthread_create(&t_check, NULL, warden, p) != 0)
		return (NULL);
	pthread_detach(t_check);
	if (p->id % 2 == 0)
		my_sleep(p->all->t_eat * 0.9);
	while (!p->all->is_dead && (p->dop_end == -1 || p->dop_end > p->dop_start))
		dinner(p);
	return (NULL);
}

void	init(t_struct *all, int i, int j, int k)
{
	void	*phil;

	while ((++i) < all->phils)
	{
		all->p[i].all = all;
		all->p[i].is_eating = sem_open("is_eating", O_CREAT, O_EXCL, 0777, 1);
		all->p[i].id = i + 1;
		all->p[i].eat = 0;
		all->p[i].dop_end = all->eat_times >= 0 ? all->eat_times : -1;
		all->p[i].dop_start = 0;
	}
	while ((++j) < all->phils)
	{
		phil = (void*)(&all->p[j]);
		if (pthread_create(&all->p[j].t, NULL, life, phil) != 0)
			return ;
	}
	while ((++k) < all->phils)
		pthread_join(all->p[k].t, NULL);
	i = -1;
	while (++i < k)
	{
		sem_close(all->p[i].is_eating);
		sem_unlink("is_eating");
	}
}

int		parse_argc(int argc, char **argv, t_struct *all)
{
	all->phils = ft_atoi(argv[1]);
	all->t_die = ft_atoi(argv[2]);
	all->t_eat = ft_atoi(argv[3]);
	all->t_sleep = ft_atoi(argv[4]);
	all->eat_times = (argc == 6) ? ft_atoi(argv[5]) : -1;
	if (all->phils < 2 || all->t_die < 4 || all->t_eat < 2 || all->t_sleep
	< 2 || all->eat_times == 0 || (argc == 6 && all->eat_times < 0))
		return (1);
	if (!(all->p = malloc(sizeof(t_phil) * all->phils)))
		return (printf("Error: memory not allocated\n"));
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("dead");
	all->forks = sem_open("forks", O_CREAT | O_EXCL, 0777, all->phils);
	all->dead = sem_open("dead", O_CREAT | O_EXCL, 0777, 1);
	all->print = sem_open("print", O_CREAT | O_EXCL, 0777, 1);
	if (all->eat_times == 0)
		all->eat_times = -1;
	all->e_t_all = all->eat_times > 0 ? all->eat_times * all->phils : -1;
	all->is_dead = 0;
	return (0);
}

int		main(int argc, char **argv)
{
	t_struct	all;

	if (argc < 5 || argc > 6)
		return (printf("%sError: Wrong number of arguments, bro \n", YELLOW));
	if (parse_argc(argc, argv, &all))
		return (printf("%sError: Wrong arguments, bro or %sYOU TRY TO FAIL MY "
					"PARSER %s %s %s\n", YELLOW, RED, ARR, ARR, ARR));
	all.time_start = now();
	init(&all, -1, -1, -1);
	sem_close(all.print);
	sem_close(all.forks);
	sem_close(all.dead);
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("dead");
	free(all.p);
	return (0);
}
