/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 08:21:56 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/16 16:27:11 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_fd(int *fd1, int *fd2)
{
	if (*fd1 != -1)
	{
		close(*fd1);
		*fd1 = -1;
	}
	if (*fd2 != -1)
	{
		close(*fd2);
		*fd2 = -1;
	}
}

void	close_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	parent_clean_fd(t_cmd *cmd)
{
	close_fd(&cmd->hfd[0]);
	(void)cmd;
}
