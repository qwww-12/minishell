/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:30:33 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 11:09:21 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free1nd(t_env *env)
{
	p1char(&env->key);
	p1char(&env->value);
	free(env);
	env = NULL;
}

static void	var_isfound(t_env **env, char *var)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, var))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free1nd(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(t_env **env, char **cmd)
{
	int		r;

	r = 1;
	while (cmd[r])
		var_isfound(env, cmd[r++]);
	e_status(0);
}
