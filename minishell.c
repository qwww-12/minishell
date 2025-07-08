/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:20 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/08 04:09:06 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

#define COLOR_RESET   "\033[0m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_RED     "\033[31m"

const char    *token_type_to_str(t_type type)
{
    if (type == WORD)
        return "WORD";
    else if (type == PIPE)
        return "PIPE";
    else if (type == REDIR_IN)
        return "REDIR_IN";
    else if (type == REDIR_OUT)
        return "REDIR_OUT";
    else if (type == APPEND)
        return "APPEND";
    else if (type == HERDOOC)
        return "HEREDOC";
    else if (type == ENV)
        return "ENV";
    return "UNKNOWN";
}

void    print_redirections(t_red *red)
{
    while (red)
    {
        printf(COLOR_YELLOW "  [REDIRECTION] " COLOR_GREEN "type: %s, "
            COLOR_WHITE "file: \"%s\", "
            COLOR_RED "expand: %d" COLOR_RESET "\n",
            token_type_to_str(red->red_type), red->file, red->expand);
        red = red->next;
    }
}

void    print_cmd_structure(t_cmd *cmd_list)
{
    int    i;

    while (cmd_list)
    {
        printf(COLOR_BLUE "---- COMMAND BLOCK ----\n" COLOR_RESET);
        if (cmd_list->commands)
        {
            i = 0;
            while (cmd_list->commands[i])
            {
                printf(COLOR_BLUE "  [ARG] " COLOR_WHITE "%s\n" COLOR_RESET,
                    cmd_list->commands[i]);
                i++;
            }
        }
        else
            printf(COLOR_BLUE "  [ARG] (none)\n" COLOR_RESET);
        if (cmd_list->red)
            print_redirections(cmd_list->red);
        else
            printf(COLOR_YELLOW "  [REDIRECTION] (none)\n" COLOR_RESET);
        
        printf(COLOR_RED "  [AMBIGUOUS] %s\n" COLOR_RESET,
            cmd_list->amb ? "true" : "false");

        cmd_list = cmd_list->next;
    }
}

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
		print_cmd_structure(cmd);
		cmdfree(cmd);
		system("leaks -q minishell");
	}
}
