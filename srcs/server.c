/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:45:02 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/19 11:48:09 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	reconstruct_char(int sig)
{
	static char	c = 0;
	static int	bits = 0;

	if (sig == SIGUSR1)
		c |= (1 << bits);
	bits++;
	if (bits == 8)
	{
		ft_putchar_fd(c, 1);
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
