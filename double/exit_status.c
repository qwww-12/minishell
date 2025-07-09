/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:57:51 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/09 23:07:56 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// void	set_e_status(int status)
// {
// 	// continue ;
// }

int	e_status(int val)
{
	static int	exit;

	if (val > -1)
		exit = val;
	return (exit);
}
