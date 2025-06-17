/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:28:15 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/01 14:45:12 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_red	*red_node(void)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (!red)
		return (NULL);
	red->next = NULL;
	return (red);
}

t_cmd	*cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->red = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}
