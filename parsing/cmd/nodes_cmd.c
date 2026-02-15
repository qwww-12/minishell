/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:28:15 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 18:09:57 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_red	*red_node(void)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (!red)
		return (NULL);
	red->next = NULL;
	return (red);
}

t_cmd	*cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->red = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->qt = 0;
	cmd->hm = 1;
	cmd->hfd[0] = -1;
	cmd->hfd[1] = -1;
	cmd->io_fd[0] = -1;
	cmd->io_fd[1] = -1;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->amb = 0;
	return (cmd);
}
