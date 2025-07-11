/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:30:33 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/11 20:38:28 by mbarhoun         ###   ########.fr       */
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

static void	remove_var(t_env *env, t_env *rmv)
{
	if (env)
		env->next = rmv->next;
	free1nd(rmv);
}

static void	var_isfound(t_env **env, char *var)
{
	t_env	*tmp;
	t_env	*envp;

	tmp = NULL;
	envp = *env;
	while (envp)
	{
		if (!ft_strcmp(envp->key, var))
		{
			if (!tmp)
			{
				tmp = envp;
				envp = envp->next;
				*env = (*env)->next;
				free1nd(tmp);
				continue ;
			}
			remove_var(tmp, *env);
		}
		tmp = envp;
		envp = envp->next;
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
