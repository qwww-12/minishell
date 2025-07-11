/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:16:30 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/11 20:37:51 by mbarhoun         ###   ########.fr       */
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
	if (is_builtin(cmd->commands[0]) && !cmd->next)
	{
		if (!set_fd_redirections(cmd) || !dup2_fd_redirections(cmd))
			return ;
		start_builtin(cmd, env);
		restore_io_fd(backup_fd);
	}
}
