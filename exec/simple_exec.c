/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 19:53:28 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_one_pipe(t_minishell *ms, t_env **env)
{
	int		id;
	char	*tmp;

	int i = 0;
	get_path(ms);
	if (parent_builtins(ms, ms->parsed, env, 0))
		return (1);
	id = fork();
	if (id == 0)
	{
		while (ms->parsed[i] && ms->parsed[i][0] == '<')
		{
			if (ms->parsed[i][1] == '<')
			{
				tmp = ms->parsed[i];
				ms->parsed[i] = quote(tmp);
				if (!here_doc(ms, ms->parsed[i] + 2, tmp + 2))
					return (0);
			}
			i++;
		}
		set_exec_signals();
		if (ms->parsed[0][0] == '<' || ms->parsed[0][0] == '>')
			ms->new_parsed = check_redir2(ms);
		else
		{
			rm_quote_last(ms->parsed);
			ms->new_parsed = ms->parsed;
		}
		if (child_builtins(ms, ms->new_parsed, env))
		{
			ft_gc_free_all();
			exit(0);
		}
		check_command(ms, ms->new_parsed[0]);
		execve(ms->path_cmd, ms->new_parsed, refresh_env(env));
	}
	waitpid(-1, &ms->status, 0);
	g_global.g_status = WEXITSTATUS(ms->status);
	remove_heredoc(ms->parsed);
	return (1);
}