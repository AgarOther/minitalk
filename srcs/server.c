/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:45:02 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/21 21:02:23 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	ft_putlst(t_list *lst)
{
	int		size;
	char	*str;
	int		i;

	size = ft_lstsize(lst);
	str = malloc(size + 1);
	if (!str)
		return ;
	i = 0;
	while (lst)
	{
		str[i] = lst->c;
		lst = lst->next;
		i++;
	}
	str[i] = 0;
	ft_putendl_fd(str, 1);
	free(str);
}

void	reconstruct_char(int sig)
{
	static char		c = 0;
	static int		bits = 0;
	static t_list	*head = NULL;
	t_list			*new_node;

	if (sig == SIGUSR1)
		c |= (1 << bits);
	bits++;
	if (bits == 8)
	{
		new_node = ft_lstnew(c);
		if (!head)
			head = new_node;
		else
			ft_lstadd_back(&head, new_node);
		if (c == 0)
		{
			ft_putlst(head);
			ft_lstcharclear(&head);
			head = NULL;
		}
		c = 0;
		bits = 0;
	}
	kill(sig, SIGUSR1);
}


void	program_stopped(int sig)
{
	(void) sig;
	ft_putstr_fd("\n\033[31mServer stopped!\033[0m\n", 1);
	exit (0);
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putstr_fd("Server's PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, reconstruct_char);
	signal(SIGUSR2, reconstruct_char);
	signal(SIGINT, program_stopped);
	while (1)
		pause();
}
