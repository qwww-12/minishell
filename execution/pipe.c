/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:04:07 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/16 16:29:53 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	dup2_fd_pipe(t_cmd *cmd)
{
	if (cmd->prev && cmd->prev->pipe_fd[0] != 0 && cmd->prev->pipe_fd[0] != -1)
	{
		if (dup2(cmd->prev->pipe_fd[0], 0) == -1)
			return (close_fd(&cmd->prev->pipe_fd[0]), eprintf(ERR_DUP2), 0);
		close_fd(&cmd->prev->pipe_fd[0]);
	}
	if (cmd->next && cmd->pipe_fd[1] != -1)
	{
		if (dup2(cmd->pipe_fd[1], 1) == -1)
			return (close_fd(&cmd->pipe_fd[1]), eprintf(ERR_DUP2), 0);
		close_fd(&cmd->pipe_fd[1]);
	}
	return (1);
}

bool	setup_fd_pipe(t_cmd *cmd)
{
	if (cmd->next && cmd->hfd[0] == -1 && cmd->io_fd[0] == -1)
		if (pipe(cmd->pipe_fd) == -1)
			return (eprintf(ERR_FPIP), 0);
	return (1);
}
