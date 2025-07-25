/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:33:46 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 12:09:54 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	run_commands(t_cmd *cmd, t_env **env)
{
	pid_t	pid;

	while (cmd)
	{
		if (!setup_fd_pipe(cmd))
			return (e_status(1), 0);
		pid = fork();
		if (pid == -1)
			return (eprintf(ERR_FORK), 0);
		else if (pid == 0)
		{
			set_signals_child();
			start_child(cmd, env);
		}
		else
			parent_clean_fd(cmd);
		cmd = cmd->next;
	}
	waiting_all_child(pid);
	return (1);
}
