/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:20 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/14 19:23:26 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*buffer;
	t_cmd	*cmd;
	t_env	*env;

	(void)ac;
	(void)av;
	env = construct_env(ev, 1);
	while (1)
	{
		rl_catch_signals = 0;
		set_signals_main();
		buffer = rd_line(env);
		cmd = assemble_commands(buffer, env);
		if (!cmd)
			continue ;
		excute_commands(cmd, &env);
		cmdfree(cmd);
	}
}
