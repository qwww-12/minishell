/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:57:51 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/16 17:23:12 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	e_status(int val)
{
	static int	exit;

	if (val > -1)
		exit = val;
	return (exit);
}

void	set_e_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			e_status(131);
			write(1, "Quit: 3\n", 8);
		}
		if (WTERMSIG(status) == SIGINT)
			e_status(130);
	}
	else if (WIFEXITED(status))
		e_status(WEXITSTATUS(status));
}

void	waiting_all_child(pid_t	lastpid)
{
	pid_t	extpid;
	int		status;

	while (1)
	{
		extpid = wait(&status);
		if (extpid < 0)
			break ;
		if (extpid == lastpid)
			set_e_status(status); 
	}
}
