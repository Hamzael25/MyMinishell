/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/31 00:18:30 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_exit_status = 0;

static int	start_minishell(t_minishell *ms)
{
	ms->line = NULL;
	ms->parsed = NULL;
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// ft_printf("okok");
		ms->line = readline(ms->prompt);
		if (!ms->line)
			return(0);
		if (is_empty(ms->line))
			continue ;
		add_history(ms->line);
		if (!check_new_line(ms))
		{
			free(ms->line);
			ft_printf("AHHHHHHHH\n");
			continue;
		}
		if (!check_write_exit(ms))
			return (free(ms->line), 0);
		// int i = 0;
		// while (ms->parsed[i])
		// {
		// 	ft_printf("%s\n", ms->parsed[i]);
		// 	i++;
		// }
		if (!exec_cmd(ms, &ms->head_env))
			return (free(ms->line), 0);
		free(ms->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argv;
	if (argc > 1)
		return (ft_dprintf(""RED"Error : Number of Arguments\n"CYAN""), 0);
	system(SHELLSCRIPT);
	init_env(&ms, envp);
	if (!start_minishell(&ms))
		return (ft_gc_free_all(), 0);
	return(0);
}
