/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:40:35 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/23 17:31:29 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ffree(char **v1, char ***v2)
{
	p1char(v1);
	p2char(v2);
}

static bool	continue_run_command(t_cmd *cmd, t_env *env)
{
	char	**anv;
	char	*path;

	if (!cmd->commands[0])
		exit(0);
	path = NULL;
	anv = environment_to_array(env);
	if (ft_strchr(cmd->commands[0], '/'))
		path = ft_strdup(cmd->commands[0]);
	else
		path = find_path(env, cmd->commands[0]);
	if (!has_slash(cmd->commands[0]) && \
		(!path || access(path, X_OK) == -1 || cmd->qt))
	{
		if (!path)
			check_permission_command(&anv, cmd->commands[0]);
		if (path && !cmd->qt)
			error_path_output(path, env);
		else
			error_path_output(cmd->commands[0], env);
		return (ffree(&path, &anv), exit(127), 1);
	}
	handle_slash(&anv, cmd->commands[0], path);
	execve(path, cmd->commands, anv);
	return (ffree(&path, &anv), exit(1), 1);
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
