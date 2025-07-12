/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:10:07 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/12 21:06:50 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ambiguous_redirect_output(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ambiguous redirect\n", 21);
}

void	file_not_found(const char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 28);
}
