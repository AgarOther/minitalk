/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:31:47 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/21 19:31:36 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, char (*f)(char), void (*del)(char))
{
	t_list	*new_list;
	t_list	*val;

	if (!f || !del || !lst)
		return (NULL);
	new_list = NULL;
	val = NULL;
	while (lst)
	{
		val = ft_lstnew(f(lst->c));
		if (!val)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, val);
		lst = lst->next;
	}
	return (new_list);
}
