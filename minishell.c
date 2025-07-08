/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:20 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/08 09:30:49 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	exit_status(int val)
{
	static int	exit;

	if (val > -1)
		exit = val;
	return (exit);
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
	history_input(rd_line);
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
		rl_catch_signals = 0;
		set_signals_main();
		buffer = rd_line(env);
		cmd = assemble_command(buffer, env);
		if (!cmd)
			continue ;
		cmdfree(cmd);
	}
}
