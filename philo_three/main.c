/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 10:18:39 by bmicheal          #+#    #+#             */
/*   Updated: 2021/02/08 17:55:10 by bmicheal         ###   ########.fr       */
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
		exit(1);
	pthread_detach(t_check);
	if (p->id % 2 == 0)
		my_sleep(p->all->t_eat * 0.9);
	while (!p->all->is_dead && (p->dop_end == -1 || p->dop_end > p->dop_start))
		dinner(p);
	if (!p->all->is_dead && p->dop_end != -1 && p->dop_start == p->dop_end)
		exit(2);
	return (NULL);
}

void	init(t_struct *all, int i, int j, int check)
{
	while ((++i) < all->phils)
	{
		all->p.pid[i] = fork();
		if (all->p.pid[i] < 0)
			return ;
		else if (all->p.pid[i] == 0)
		{
			all->p.id = i + 1;
			life((void*)&all->p);
		}
	}
	while (1)
	{
		waitpid(-1, &all->status, 0);
		if (WEXITSTATUS(all->status) == 1)
			break ;
		else if (WEXITSTATUS(all->status) == 2)
		{
			check++;
			if (check == all->phils)
				break ;
		}
	}
	while (++j < all->phils)
		kill(all->p.pid[j], SIGTERM);
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
	if (!(all->p.pid = malloc(sizeof(pid_t) * all->phils)))
		return (printf("Error: memory not allocated\n"));
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("dead");
	sem_unlink("is_eating");
	all->p.is_eating = sem_open("is_eating", O_CREAT, O_EXCL, 0777, 1);
	all->forks = sem_open("forks", O_CREAT | O_EXCL, 0777, all->phils);
	all->dead = sem_open("dead", O_CREAT | O_EXCL, 0777, 1);
	all->print = sem_open("print", O_CREAT | O_EXCL, 0777, 1);
	all->eat_times -= (all->eat_times == 0) ? 1 : 0;
	all->e_t_all = (all->eat_times > 0) ? all->phils : -1;
	all->is_dead = 0;
	all->status = 0;
	all->p.dop_end = all->eat_times >= 0 ? all->eat_times : -1;
	all->p.dop_start = 0;
	return (0);
}

int		main(int argc, char **argv)
{
	t_struct	all;

	all.p.all = &all;
	if (argc < 5 || argc > 6)
		return (printf("%sError: Wrong number of arguments, bro \n", YELLOW));
	if (parse_argc(argc, argv, &all))
		return (printf("%sError: Wrong arguments, bro or %sYOU TRY TO FAIL MY "
					"PARSER %s %s %s\n", YELLOW, RED, ARR, ARR, ARR));
	all.time_start = now();
	init(&all, -1, -1, 0);
	sem_close(all.print);
	sem_close(all.forks);
	sem_close(all.dead);
	sem_close(all.p.is_eating);
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("dead");
	sem_unlink("is_eating");
	free(all.p.pid);
	return (0);
}
