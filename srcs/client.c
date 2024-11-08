/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:37:41 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/08 20:21:58 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_allow_signal = 0;

void	allow_signal(int pid)
{
	(void) pid;
	g_allow_signal = 1;
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
		while (!g_allow_signal)
			pause();
		g_allow_signal = 0;
	}
}

static int	is_pid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	has_valid_args(int argc, char **argv)
{
	if (argc == 1 || argc > 3)
	{
		ft_putstr_fd
			("\033[31m[Error] Expected server PID and message.\033[0m\n", 1);
		return (0);
	}
	else if (argc == 2)
	{
		ft_putstr_fd
			("\033[31m[Error] Expected message after PID.\033[0m\n", 1);
		return (0);
	}
	if (!is_pid(argv[1]))
	{
		ft_putstr_fd
			("\033[31m[Error] Invalid PID.\033[0m\n", 1);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (!has_valid_args(argc, argv))
		return (0);
	pid = ft_atoi(argv[1]);
	if (pid < 0)
		return (0);
	str = argv[2];
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
	return (0);
}
