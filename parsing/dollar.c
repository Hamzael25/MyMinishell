/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:33:33 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/05/18 08:39:56 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**do_real_null(char **ms_parsed, int count)
{
	char	**new_ms;
	int		j;
	int		i;

	new_ms = ft_calloc_parent(sizeof(char *), (count + 1), "parsing");
	i = 0;
	j = 0;
	while (ms_parsed[i])
	{
		if (ms_parsed[i][0])
		{
			new_ms[j] = ft_strdup(ms_parsed[i]);
			if (!new_ms[j])
				exit_parent("parsing");
			j++;
		}
		i++;
	}
	new_ms[j] = 0;
	return (new_ms);
}

char	**real_null(char **ms_parsed)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (ms_parsed[i])
	{
		if (ms_parsed[i][0])
			count++;
		i++;
	}
	return (do_real_null(ms_parsed, count));
}

int	size_new_parsed(t_minishell *ms)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = 0;
	while (ms->parsed[i])
	{
		if (ft_strnstr(ms->parsed[i], "$", ft_strlen(ms->parsed[i])) != 0)
		{
			j = 0;
			ms->tmp_dollar = change_parsed_dollar(ms, ms->parsed[i], 0, 0);
			while (ms->tmp_dollar[j])
			{
				size++;
				j++;
			}
			i++;
			continue ;
		}
		size++;
		i++;
	}
	return (size);
}

void	realloc_dollar(t_minishell *ms, int size)
{
	int		i;
	int		j;

	i = -1;
	while (ms->parsed[++i])
	{
		if (ft_strnstr(ms->parsed[i], "$", ft_strlen(ms->parsed[i])) != 0)
		{
			j = -1;
			ms->tmp_dollar = change_parsed_dollar(ms, ms->parsed[i], 0, 0);
			while (ms->tmp_dollar[++j])
			{
				ms->realloc[size] = ft_strdup(ms->tmp_dollar[j]);
				if (!ms->realloc[size])
					exit_parent("parsing");
				size++;
			}
			continue ;
		}
		ms->realloc[size] = ft_strdup(ms->parsed[i]);
		if (!ms->realloc[size])
			exit_parent("parsing");
		size++;
	}
	ms->realloc[size] = 0;
	// printf("REALL %d\n", size);
}

// int	is_null(char **realloc)
// {

// 	while (realloc)
// }

void	check_dollar(t_minishell *ms, int mod)
{
	int	i;

	// i = 0;
	// while (ms->parsed[i])
	// {
	// 	printf("ms parsed[%i] %s\n", i, ms->parsed[i]);
	// 	i++;
	// }
	// printf("sizdebut %d\n", i);
	i = 0;
	ms->realloc = NULL;
	ms->realloc = ft_calloc_parent(sizeof(char *), \
		(size_new_parsed(ms) + 1), "parsing");
	realloc_dollar(ms, i);
	if (!mod)
	{
		if (ms->realloc[0] && ms->realloc[1])
			ms->realloc = real_null(ms->realloc);
	}
	ms->parsed = ms->realloc;
	// i = 0;
	// while (ms->parsed[i])
	// {
	// 	// int j = 0;
	// 	// if (!ms->parsed[i][0])
	// 	// 	printf("je suis vide a %d\n", i);
	// 	// while (ms->parsed[i][j])
	// 	// {
	// 	// 	j++;
	// 	// }
	// 	// printf("SIZE %d\n", j);
	// 	printf("ms->parse[%i] = %s\n", i, ms->parsed[i]);
	// 	i++;
	// }
	// printf("sizfin %d\n", i);
}
