/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:56:24 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/10 20:02:11 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=", env->key);
		printf("%s\n", env->value);
		env = env->next;
	}
	e_status(0);
}
