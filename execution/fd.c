/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:46:32 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/10 18:22:12 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	restore_io_fd(int *fds)
{
	if (dup2(fds[0], 0) == -1)
		return (eprintf(ERR_DUP2), 0);
	if (dup2(fds[1], 1) == -1)
		return (eprintf(ERR_DUP2), 0);
	return (1);
}

bool	store_io_fd(int *fds)
{
	fds[0] = dup(0);
	fds[1] = dup(1);
	if (fds[0] == -1 || fds[1] == -1)
		return (eprintf(ERR_DUP), 0);
	return (1);
}
