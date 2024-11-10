/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:40:34 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/10 12:46:27 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
