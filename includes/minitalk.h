/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:21:20 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/19 11:15:13 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Name of Header
#ifndef MINITALK_H
# define MINITALK_H

// Define usleep time (wait time between signals).
// Higher value means more execution time but more accurate.
// Lower value means less accurate but faster.
// /!\ Values that are too small WON'T work!
// [Default: 100]
# ifndef SLEEP_TIME
#  define SLEEP_TIME 100
# endif

// Includes
# include <signal.h>
# include <unistd.h>
# include "../libft/libft.h"
#endif