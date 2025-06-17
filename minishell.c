/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:20 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/16 18:09:52 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*rd_line(t_env *env)
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

void ctrl_c(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1); 
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();               
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
		buffer = rd_line(env);
		cmd = assemble_command(buffer, env);
		if (!cmd)
			continue ;
		cmdfree(cmd);
	}
}
