/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:45:02 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/21 16:56:14 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_chardup(char c)
{
	char	*new;

	new = malloc(1);
	*new = c;
	return (new);
}

#include <stdio.h>

void	ft_putlst(t_list *lst)
{
	int		size;
	char	*str;

	size = ft_lstsize(lst);
	printf("size: %d\n", size);
	str = malloc(size + 1);
	if (!str)
		return ;
	while (lst)
	{
		*str = *(char*)lst->content;
		lst = lst->next;
		str++;
	}
	*str = 0;
	ft_putstr_fd(str, 1);
	//free(str);
}

void	reconstruct_char(int sig)
{
	static char		c = 0;
	static int		bits = 0;
	static t_list	*str = NULL;
	static t_list	*head;

	if (sig == SIGUSR1)
		c |= (1 << bits);
	bits++;
	if (bits == 8)
	{
		printf("bit received: %d (%c)\n", c, c);
		str = ft_lstnew(ft_chardup(c));
		if (!head)
			head = str;
		printf("char received: %d (%c)\n", *(char*)str->content, *(char*)str->content);
		str = str->next;
		if (c == 0)
			ft_putlst(head);
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
