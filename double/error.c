/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:08:24 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 19:58:25 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	minishell_error_output(char *erm)
{
	write(2, "minishell: ", 11);
	perror(erm);
}

void print_errno_info(char *erm)
{
	if (errno == EACCES)
		minishell_error_output(erm);
	else if (errno == ENOENT)
		minishell_error_output(erm);
	else if (errno == EISDIR)
		minishell_error_output(erm);
	else if (errno == ENOTDIR)
		minishell_error_output(erm);
}

void	eprintf(const char *str)
{
	write(2, str, ft_strlen(str));
}
