/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evar_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:10:07 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/23 17:29:27 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_permission_command(char ***env, char *cmd)
{
	if (access(cmd, F_OK) != -1 && access(cmd, X_OK) == -1)
	{
		print_errno_info(NULL);
		p2char(env);
		exit(126);
	}
}

void	is_not_directory(char *dir)
{
	write(2, "minishell: ", 11);
	write(2, dir, ft_strlen(dir));
	write(2, ": No such file or directory\n", 28);
}

void	is_directory(char *dir)
{
	write(2, "minishell: ", 11);
	write(2, dir, ft_strlen(dir));
	write(2, ": is a directory\n", 17);
}

void	ambiguous_redirect_output(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ambiguous redirect\n", 21);
}
