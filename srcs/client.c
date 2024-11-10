/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:37:41 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/10 13:14:39 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_allow_signal = 0;

void	allow_signal(int pid)
{
	(void) pid;
	g_allow_signal = 1;
}

void	await_signal(void)
{
	int	timeout;

	timeout = 0;
	while (timeout <= 10000 && !g_allow_signal)
	{
		usleep(1);
		timeout++;
	}
	if (timeout >= 10000)
	{
		ft_putendl_fd("\n\033[31mNo response from server, aborting!\033[0m", 1);
		sleep(1);
		exit(0);
	}
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		signal(SIGUSR1, allow_signal);
		await_signal();
		g_allow_signal = 0;
	}
}

void	server_message(int pid)
{
	(void) pid;
	ft_putendl_fd("\033[0;32mServer successfully received a message!", 1);
	exit(0);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (!has_valid_args(argc, argv))
		return (0);
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0))
	{
		ft_putstr_fd
			("\033[31m[Error] Invalid PID.\033[0m\n", 1);
		return (0);
	}
	str = argv[2];
	signal(SIGUSR2, server_message);
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
	return (0);
}
