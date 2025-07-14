/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:33:46 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/14 18:52:08 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	run_commands(t_cmd *cmd, t_env **env, int *back_up)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (eprintf(ERR_FORK), 0);
	else if (pid == 0)
	{
		set_signals_child();
		start_child(cmd, env, back_up);
	}
	wait(&status);
	set_e_status(status);
	restore_io_fd(back_up);
	return (1);
}
