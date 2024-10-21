/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:02:18 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/11 13:59:30 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	has_character(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strcpy(char *dest, char const *src, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (has_character(s1[start], set))
		start++;
	while (has_character(s1[end], set))
		end--;
	if (start > end)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	str = malloc(end - start + 2);
	if (!str)
		return (NULL);
	str = ft_strcpy(str, s1, start, end);
	return (str);
}
