/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:19:12 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/29 16:53:20 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include "/Users/mbarhoun/.brew/opt/readline/include/readline/readline.h"
# include "/Users/mbarhoun/.brew/opt/readline/include/readline/history.h"
# include "./parsing/include/token.h"
# include "./parsing/include/syntax.h"
# include "./libft/libft.h"

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;
typedef struct s_red	t_red;

typedef struct s_env
{
	char	*key;
	char	*value;
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
	t_red	*red;
	t_cmd	*prev;
	t_cmd	*next;
}	t_cmd;

/*~~~~~~~~~~~~~~~~~~~~~~<minishell.c>~~~~~~~~~~~~~~~~~~~~~~*/
int		exit_status(int value);
void	change_gsig1(int val);

#endif