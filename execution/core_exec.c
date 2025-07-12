/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:16:30 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/12 21:53:53 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excute_commands(t_cmd *cmd, t_env **env)
{
	int		backup_fd[2];

	signal(SIGINT, SIG_IGN);
	if (!setup_heredocs(cmd, *env))
		return ;
	store_io_fd(backup_fd);
	if ((is_builtin(cmd) && !cmd->next) || (cmd && !cmd->commands[0]))
	{
		if (!set_fd_redirections(cmd) || !dup2_fd_redirections(cmd))
			return ;
		start_builtin(cmd, env);
		close_all_fd(&cmd->io_fd[0], &cmd->io_fd[1]);
		restore_io_fd(backup_fd);
	}
}
