/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:45:02 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/10 13:15:53 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putlst(t_list *lst, int pid)
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
	kill(pid, SIGUSR2);
}

void	interrupt(t_list **head, void *context)
{
	(void) context;
	ft_lstcharclear(head);
	usleep(10000);
	ft_putendl_fd("\n\033[31mServer closed and leak-free!\033[0m", 1);
	sleep(1);
	exit(0);
}

void	reconstruct_char(int sig, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		bits = 0;
	static t_list	*head = NULL;
	t_list			*new_node;

	if (sig == SIGUSR1)
		c |= (1 << bits);
	else if (sig == SIGINT)
		return (interrupt(&head, context));
	if (++bits == 8)
	{
		new_node = ft_lstnew(c);
		if (!head)
			head = new_node;
		else
			ft_lstadd_back(&head, new_node);
		if (c == 0)
		{
			ft_putlst(head, info->si_pid);
			ft_lstcharclear(&head);
		}
		c = 0;
		bits = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	print_shrek(void)
{
	ft_putendl_fd("\033[92m", 1);
	ft_putendl_fd("⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆", 1);
	ft_putendl_fd("⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿", 1);
	ft_putendl_fd("⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀", 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("\033[0m", 1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sig;

	pid = getpid();
	print_shrek();
	ft_putstr_fd("Server's PID:	", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = reconstruct_char;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
	while (1)
		pause();
}
