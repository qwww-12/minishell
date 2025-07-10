/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:16:30 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/10 11:07:34 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excute_commands(t_cmd *cmd, t_env *env)
{
	signal(SIGINT, SIG_IGN);
	if (!setup_heredocs(cmd, env))
		return ;
	
}
