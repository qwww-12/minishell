/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:18:34 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 18:22:45 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_builtin(t_cmd *cmd)
{
	if (!cmd->commands[0])
		return (0);
	if (!ft_strcmp(cmd->commands[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd->commands[0], "export"))
		return (1);
	if (!ft_strcmp(cmd->commands[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->commands[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd->commands[0], "env"))
		return (1);
	if (!ft_strcmp(cmd->commands[0], "cd"))
		return (1);
	return (0);
}

void	start_builtin(t_cmd *cmd, t_env **env)
{
	if (!cmd->commands[0])
		return ;
	if (!ft_strcmp(cmd->commands[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->commands[0], "export"))
		ft_export(*env, cmd->commands);
	else if (!ft_strcmp(cmd->commands[0], "unset"))
		ft_unset(env, cmd->commands);
	else if (!ft_strcmp(cmd->commands[0], "exit"))
		ft_exit(cmd, *env, cmd->commands);
	else if (!ft_strcmp(cmd->commands[0], "env") && !cmd->commands[1])
		ft_env(*env);
	else if (!ft_strcmp(cmd->commands[0], "cd"))
		ft_cd(*env, &cmd->commands[1], cmd->hm);
}
