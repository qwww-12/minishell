/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:40:35 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/19 18:37:04 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	continue_run_command(t_cmd *cmd, t_env *env)
{
	char	**anv;
	char	*path;

	if (!cmd->commands[0])
		exit(0);
	anv = environment_to_array(env);
	if (ft_strchr(cmd->commands[0], '/'))
		path = ft_strdup(cmd->commands[0]);
	else
		path = find_path(env, cmd->commands[0]);
	if (!path || access(path, X_OK) == -1 || cmd->qt)
	{
		if (path && !cmd->qt)
			error_path_output(path, env);
		else
			error_path_output(cmd->commands[0], env);
		p1char(&path);
		p2char(&anv);
		exit(127);
	}
	execve(path, cmd->commands, anv);
	p1char(&path);
	p2char(&anv);
	exit(1);
}

void	start_child(t_cmd *cmd, t_env **env)
{
	if (!dup2_fd_pipe(cmd))
		exit(1);
	if (!set_fd_redirections(cmd) || !dup2_fd_redirections(cmd))
		exit(1);
	if (is_builtin(cmd))
	{
		start_builtin(cmd, env);
		exit(e_status(-1));
	}
	else
		continue_run_command(cmd, *env);
}
