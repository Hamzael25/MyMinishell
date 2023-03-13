/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:29:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/13 12:16:47 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

t_env	*ft_lstlas(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_env	*create_cell(char *var, char *content)
{
	t_env	*cell;

	cell = ft_gc_malloc(sizeof(t_env));
	if (!cell)
		return (cell);
	cell->key = var;
	cell->value = content;
	cell->next = NULL;
	return (cell);
}

void	ft_lstad_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlas(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

int	lstsize(t_env *lst)
{
	int	i;
	t_env *cpy;
	cpy = lst;

	i = 0;
	while (cpy)
	{
		cpy = cpy->next;
		i++;
	}
	return (i);
}
