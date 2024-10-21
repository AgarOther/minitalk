/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:37:41 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/21 21:07:54 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		usleep(SLEEP_TIME);
	}
}

int	is_pid(char *str)
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

void test(int sig)
{
	(void) sig;
	ft_putstr_fd("oue", 1);
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
	signal(SIGUSR1, test);
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	usleep(SLEEP_TIME * 1.5);
	send_char(pid, '\0');
	return (0);
}
