/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:48:35 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/17 19:14:04 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	error_exit_output(char *arg)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
}

static void	too_many_arguments(void)
{
	eprintf(ERR_MANY_ARGS);
	e_status(1);
}

static void	char_exit(t_cmd *cmd, t_env *env, char *arg, char c)
{
	if (!ft_isdigit(c))
	{
		error_exit_output(arg);
		env_leaks(env);
		cmdfree(cmd);
		write(1, "exit\n", 5);
		exit(255);
	}
}

static void	exit_clean(t_cmd *cmd, t_env *env, char *num, bool ffree)
{
	size_t	ext;

	ext = 0;
	env_leaks(env);
	write(1, "exit\n", 5);
	if (!is_overflow(num, &ext))
	{
		if (ffree)
			p1char(&num);
		cmdfree(cmd);
		exit(((ext % 256) + 256) % 256);
	}
	error_exit_output(num);
	exit(255);
}

void	ft_exit(t_cmd *tmd, t_env *env, char **cmd)
{
	int		r;
	int		f;

	r = 0;
	f = 0;
	while (cmd[++r])
	{
		if (r == 2)
		{
			too_many_arguments();
			return ;
		}
		f = -1;
		while (cmd[r][++f])
			char_exit(tmd, env, cmd[r], cmd[r][f]);
	}
	if (r - 1 == 0)
		exit_clean(tmd, env, ft_itoa(e_status(-1)), 1);
	else
		exit_clean(tmd, env, cmd[r - 1], 0);
}
