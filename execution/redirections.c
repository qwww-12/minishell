/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:45:01 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/13 15:59:07 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	set_fd_outfile(t_cmd *cmd, t_red *red)
{
	if (cmd->io_fd[1] != -1)
		close_fd(&cmd->io_fd[1]);
	if (red->red_type == REDIR_OUT)
	{
		cmd->io_fd[1] = open(red->file, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (cmd->io_fd[1] == -1)
			return (0);
	}
	else
	{
		cmd->io_fd[1] = open(red->file, O_CREAT | O_APPEND | O_RDWR, 0777);
		if (cmd->io_fd[1] == -1)
			return (0);
	}
	return (1);
}

static bool	set_fd_infile(t_cmd *cmd, t_red *red)
{
	if (cmd->io_fd[0] != -1)
		close_fd(&cmd->io_fd[0]);
	if (red->red_type == REDIR_IN)
	{
		cmd->io_fd[0] = open(red->file, O_RDONLY, 0777);
		if (cmd->io_fd[0] == -1)
			return (file_not_found(red->file), 0);
	}
	else
		cmd->io_fd[0] = cmd->hfd[0];
	return (1);
}

bool	set_fd_redirections(t_cmd *cmd)
{
	t_red	*red;

	red = cmd->red;
	while (red)
	{
		if (red->red_type == REDIR_OUT || red->red_type == APPEND)
			if (!set_fd_outfile(cmd, red))
				return (0);
		if (red->red_type == REDIR_IN || red->red_type == HERDOOC)
			if (!set_fd_infile(cmd, red))
				return (0);
		if (red->red_type == AMB)
		{
			close_all_fd(&cmd->io_fd[0], &cmd->io_fd[1]);
			ambiguous_redirect_output(red->file);
			return (0);
		}
		red = red->next;
	}
	return (1);
}

bool	dup2_fd_redirections(t_cmd *cmd)
{
	if (cmd->io_fd[0] != 0 && cmd->io_fd[0] != -1)
	{
		if (dup2(cmd->io_fd[0], 0) == -1)
			return (eprintf(ERR_DUP2), 0);
		close(cmd->io_fd[0]);
	}
	if (cmd->io_fd[1] != 1 && cmd->io_fd[1] != -1)
	{
		if (dup2(cmd->io_fd[1], 1) == -1)
			return (eprintf(ERR_DUP2), 0);
		close(cmd->io_fd[1]);
	}
	return (1);
}
