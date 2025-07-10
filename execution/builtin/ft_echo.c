/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:30:24 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/10 18:55:01 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_arguments_nl(char *content)
{
	int	r;

	r = 0;
	while (content[++r])
		if (content[r] != 'n')
			return (0);
	return (1);
}

static int	arguments_nl(t_cmd **cmd)
{
	int		nl;
	int		r;

	nl = 0;
	r = 1;
	while ((*cmd)->commands[r])
	{
		if ((*cmd)->commands[r][0] == '-')
		{
			if (is_arguments_nl((*cmd)->commands[r]) == 1)
				nl++;
			else
				return (nl);
		}
		if (!nl)
			break ;
		r++;
	}
	return (nl);
}

void	ft_echo(t_cmd *cmd)
{
	int		nl;
	int		r;

	nl = arguments_nl(&cmd);
	r = 1;
	if (nl > 0)
		r += nl;
	while (cmd->commands[r])
	{
		write(1, cmd->commands[r], ft_strlen(cmd->commands[r]));
		if (cmd->commands[r + 1])
			write(1, " ", 1);
		r++;
	}
	if (!nl)
		write(1, "\n", 1);
	e_status(0);
}
