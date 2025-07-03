/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:20 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/03 18:06:26 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

bool	g_sig = 0;

void	change_gsig1(int val)
{
	g_sig = val;
	if (val == 1)
		signal(SIGQUIT, SIG_DFL);
	else
		signal(SIGQUIT, SIG_IGN);
}

int	exit_status(int val)
{
	static int	exit;

	if (val > -1)
		exit = val;
	return (exit);
}

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit_status(130);
	if (g_sig == 0)
	{
		rl_redisplay();
		exit_status(1);
	}
}

static char	*rd_line(t_env *env)
{
	char	*rd_line;

	rd_line = NULL;
	rd_line = readline("minishell-$> ");
	if (!rd_line)
	{
		env_leaks(env);
		printf("\033[1A");
		printf("\033[13C");
		printf("exit\n");
		exit(0);
	}
	glance_input(rd_line, env);
	return (rd_line);
}

int	main(int ac, char **av, char **ev)
{
	char	*buffer;
	t_cmd	*cmd;
	t_env	*env;

	(void)ac;
	(void)av;
	env = construct_env(ev);
	while (1)
	{
		signal(SIGINT, ctrl_c);
		if (g_sig == 1)
			signal(SIGQUIT, SIG_DFL);
		rl_catch_signals = 0;
		buffer = rd_line(env);
		cmd = assemble_command(buffer, env);
		if (!cmd)
			continue ;
		cmdfree(cmd);
		system("leaks -q minishell");
	}
}
