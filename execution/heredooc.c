/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredooc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 08:02:14 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/10 15:19:01 by mbarhoun         ###   ########.fr       */
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

static char	*prompt_heredooc(void)
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
			ft_putstr_fd(line, cmd->hfd[WRITE]);
		else
			resolve_heredoc(env, &line, cmd->hfd[WRITE]);
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
		return (close_fd(&cmd->hfd[WRITE]), eprintf(ERR_FORK), 0);
	else if (pid == 0)
	{
		set_signals_heredoc();
		close_fd(&cmd->hfd[READ]);
		run_heredooc(cmd, red, env);
		exit(0);
	}
	waitpid(pid, &status, 0);
	set_e_status(status);
	if (e_status(-1) == 1)
		return (0);
	return (1);
}

bool	setup_heredocs(t_cmd *cmd, t_env *env)
{
	t_red	*red;

	while (cmd)
	{
		red = cmd->red;
		while (red)
		{
			if (cmd->hfd[WRITE] != -1)
				close_fd(&cmd->hfd[WRITE]);
			if (pipe(cmd->hfd) == -1)
				return (eprintf(ERR_FPIP), 0);
			if (red->red_type == HERDOOC)
				if (!fork_heredooc(cmd, red, env))
					return (close_fd(&cmd->hfd[WRITE]), 0);
			red = red->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
