/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:18:34 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/11 18:30:13 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	return (0);
}

void	start_builtin(t_cmd *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->commands[0], "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd->commands[0], "export"))
		ft_export(env, cmd->commands);
	if (!ft_strcmp(cmd->commands[0], "unset"))
		ft_unset(env, cmd->commands);
	if (!ft_strcmp(cmd->commands[0], "env") && !cmd->commands[1])
		ft_env(env);
}
