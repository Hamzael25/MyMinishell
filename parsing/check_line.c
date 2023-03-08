/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:22:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/08 18:18:39 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quote_2(char *line, char *str)
{
	int		i;
	int		i2;
	char	c;

	str = ft_calloc(sizeof(char), (ft_strlen(line) - 2 + 1));
	i = 0;
	i2 = 0;
	while (line[i2])
	{
		if (line[i2] && ft_strchr("\'\"", line[i2]))
		{
			c = line[i2++];
			while (line[i2] && line[i2] != c)
				str[i++] = line[i2++];
			i2++;
		}
		else if (line[i2])
			str[i++] = line[i2++];
	}
	str[i] = 0;
	return (str);
}

char	*quote(char *line)
{
	char	*str;

	str = NULL;
	if (!line)
		return (0);
	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
		str = quote_2(line, str);
	else
		return (line);
	return (str);
}

static void del_char(t_minishell *ms)
{
    int size;
    int i;
	int j;
    
    i = 0;
    size = 0;
    while (ms->line[i])
    {
        if (ms->line[i] != 92 && ms->line[i] != ';')
            size++;
		i++;
    }
    ms->new_line = malloc(sizeof(char) * (size + 1));
    if (!ms->new_line)
    {
        free(ms->new_line);
        return ;
    }
    i = 0;
    j = 0;
    while (ms->line[i])
    {
        if (ms->line[i] != 92 && ms->line[i] != ';')
		{
            ms->new_line[j] = ms->line[i];
			j++;
		}
		i++;

    }
    ms->new_line[j] = 0;
}

void new(t_minishell *ms, char **space)
{
    int i;
    char **quot;

    quot = (char**)malloc(sizeof(char *) * (ft_strlen(*space) + 1));
	ms->parsed = (char **)malloc(sizeof(char *) * ft_strlen(*space) + 1);
    i = 0;
    while (space[i])
    {
        quot[i] = ft_strdup(quote(space[i]));
        i++;
    }
    quot[i] = 0;
    i = 0;
    while (quot[i])
    {
        ms->parsed[i] = ft_strdup(quot[i]);
        i++;
    }
    ms->parsed[i] = 0;
    ft_free_tab(quot);
}

void    ft_pipe(t_minishell *ms)
{
    char	**pipe;
	char	**space;
	int		i;
    int j = 0;
	
    pipe = ft_split(ms->new_line, '|');
	ms->joined = (char **)malloc(sizeof(char *) * (ft_strlen(*pipe) + 1));
	j = 0;
    while (pipe[j])
    {
        space = ft_split(pipe[j], ' ');
        new(ms, space);
		i = 0;
		ms->joined[j] = NULL;
		while (ms->parsed[i])
		{
			ms->joined[j] = ft_strjoin_gnl(ms->joined[j], ms->parsed[i]);
			ms->joined[j] = ft_strjoin_gnl(ms->joined[j], " ");
			i++;
		}
		ms->parsed[i] = 0;
        j++;
    }
	ms->joined[j] = 0;
	//ft_free_tab(pipe);
}

void check_new_line(t_minishell *ms)
{
	char	**space;
    int i;
    
    i = 0;
    if (ft_strchr(ms->line, 92) || ft_strchr(ms->line, ';'))
        del_char(ms);
    else
        ms->new_line = ms->line;
    if (ft_strchr(ms->new_line, '|'))
	{
        ft_pipe(ms);
		while (ms->joined[i])
			i++;
		ft_free_tab(ms->parsed);
		ms->parsed = malloc(sizeof(char *) * (i + 1));
		i = 0;
		while(ms->joined[i])
		{
			ms->parsed[i] = ms->joined[i];
			i++;
		}
		ms->joined[i] = 0;
		ms->parsed[i] = 0;
		//ft_free_tab(ms->joined);
	}
    else
	{
		space = ft_split(ms->new_line, ' ');
        new(ms, space);
		ft_free_tab(space);
	}
}