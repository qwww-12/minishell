/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:16:30 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 12:00:44 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	excute_commands(t_cmd *cmd, t_env **env)
{
	int		backup_fd[2];

	signal(SIGINT, SIG_IGN);
	if (!setup_heredocs(cmd, *env))
		return (0);
	store_io_fd(backup_fd);
	if ((is_builtin(cmd) && !cmd->next))
	{
		if (!set_fd_redirections(cmd) || !dup2_fd_redirections(cmd))
			return (e_status(1), 0);
		start_builtin(cmd, env);
	}
	else
		run_commands(cmd, env, backup_fd);
	restore_io_fd(backup_fd);
	return (1);
}
