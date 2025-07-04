/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:17:01 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/04 00:39:58 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit_status(130);
	if (control_g(0, 0) == 0)
	{
		rl_redisplay();
		exit_status(1);
	}
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	if (control_g(0, 0) == 1)
		exit_status(131);
}

void	set_signals_main(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL); // i don't know
	signal(SIGQUIT, SIG_DFL);// i don't know
}
