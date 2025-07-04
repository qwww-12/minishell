/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:17:36 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/04 08:15:57 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	glance_input(char *input, t_env *env)
{
	if (!input)
		exit(0);
	if (!ft_strcmp(input, "exit"))
	{
		env_leaks(env);
		printf("exit\n");
		exit(0);
	}
	if (input[0] == '\0')
		return ;
	add_history(input);
}
