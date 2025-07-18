/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:19:12 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 19:13:38 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "/Users/mbarhoun/.brew/opt/readline/include/readline/readline.h"
# include "/Users/mbarhoun/.brew/opt/readline/include/readline/history.h"
# include "./libft/libft.h"
# include "./execution/get_next_line/gnl.h"
# include "./parsing/include/parsing.h"
# include "./execution/include/exec.h"

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;
typedef struct s_red	t_red;

typedef struct s_env
{
	char	*key;
	char	*value;
	bool	eq;
	t_env	*next;
}	t_env;

typedef struct s_red
{
	char	*file;
	bool	expand;
	t_type	red_type;
	t_red	*next;
}	t_red;

typedef struct s_cmd
{
	char	**commands;
	int		hfd[2];
	int		io_fd[2];
	int		pipe_fd[2];
	bool	amb;
	bool	qt;
	bool	hm;
	t_red	*red;
	t_cmd	*prev;
	t_cmd	*next;
}	t_cmd;

/*~~~~~~~~~~~~~~~~~~~~~~~<exit_status.c>~~~~~~~~~~~~~~~~~~~~~~~*/
int			e_status(int val);
void		set_e_status(int status);
void		waiting_all_child(pid_t	lastpid);
/*~~~~~~~~~~~~~~~~~~~~~~<error.c>~~~~~~~~~~~~~~~~~~~~~~*/
void		eprintf(const char *str);
void		print_errno_info(char *erm);
/*~~~~~~~~~~~~~~~~~~~~~~<leaks.c>~~~~~~~~~~~~~~~~~~~~~~*/
void		first_free(t_token *tokens, char *input);
void		p1char(char **ptr);
void		p2char(char ***ptr);
void		cmdfree(t_cmd *cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<signal.c>~~~~~~~~~~~~~~~~~~~~~~*/
void		set_signals_main(void);
void		set_signals_child(void);
void		set_signals_heredoc(void);

#endif