/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredooc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 08:02:14 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/10 11:31:43 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*delete_newline(char *line)
{
	char	*new;
	int		r;

	new = malloc(sizeof(char) * ft_strlen(line));
	if (!new)
		return (eprintf(ERR_MEM), NULL);
	r = 0;
	while (line[r] && line[r] != '\n')
	{
		new[r] = line[r];
		r++;
	}
	new[r] = '\0';
	p1char(&line);
	return (new);
}

static char *prompt_heredooc()
{
	char	*line;

	line = NULL;
	write(1, "> ", 2);
	line = get_next_line(1);
	if (line)
		line = delete_newline(line);
	return (line);
}

static void	run_heredooc(t_cmd *cmd, t_red *red, t_env *env)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = prompt_heredooc();
		if (!line)
			break ;
		else if (!ft_strcmp(line, red->file))
			break ;
		else if (line && red->expand == 0)
			ft_putstr_fd(line, cmd->pipefd[WRITE]);
		else
			resolve_heredoc(env, &line, cmd->pipefd[WRITE]);
		p1char(&line);
	}
	p1char(&line);
}

static bool	fork_heredooc(t_cmd *cmd, t_red *red, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (eprintf(ERR_FORK), 0);
	else if (pid == 0)
	{
		set_signals_heredoc();
		close_fd(&cmd->pipefd[READ]);
		run_heredooc(cmd, red, env);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		set_e_status(status);
		if (e_status(-1) == 1)
			return (0);
	}
	return (1);
}

bool	setup_heredocs(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmd;
	t_red	*red;

	tmd = cmd;
	while (tmd)
	{
		red = tmd->red;
		while (red)
		{
			if (pipe(tmd->pipefd) == -1)
				return (eprintf(ERR_FPIP), 0);
			if (red->red_type == HERDOOC)
				if (!fork_heredooc(tmd, red, env))
					return (0);
			red = red->next;
		}
		tmd = tmd->next;
	}
	return (1);
}
