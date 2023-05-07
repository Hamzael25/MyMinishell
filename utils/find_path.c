/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:52:48 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/07 15:44:59 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**refresh_env(t_env **env)
{
	t_env	*head;
	char	**new_env;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	head = *env;
	new_env = (char **)ft_gc_malloc(sizeof(char *) * (lstsize(*env) + 1));
	while (head)
	{
		if (!head->value)
			new_env[i] = ft_gc_malloc(sizeof(char) * \
				(ft_strlen(head->key) + 1));
		else
			new_env[i] = ft_gc_malloc(sizeof(char) * \
				(ft_strlen(head->key) + ft_strlen(head->value) + 2));
		j = 0;
		k = 0;
		while (head->key[k])
			new_env[i][j++] = head->key[k++];
		if (!head->value)
		{
			head = head->next;
			continue ;
		}
		new_env[i][j] = '=';
		j++;
		k = 0;
		while (head->value[k])
			new_env[i][j++] = head->value[k++];
		new_env[i][j] = 0;
		head = head->next;
		i++;
	}
	return (new_env[i] = 0, new_env);
}

char	*ft_find_path(t_env **env, char *srch)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (!ft_strncmp(head->key, srch, ft_strlen(srch) + 1))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}
