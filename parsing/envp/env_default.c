/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:45:51 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/19 18:37:20 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	env_key(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	add_default_env(t_env *env)
{
	if (!env_key("OLDPWD", env))
		list_add_back(&env, new_env(ft_strdup("OLDPWD"), ft_strdup(""), 0));
	if (!env_key("PWD", env))
		list_add_back(&env, new_env(ft_strdup("PWD"), getcwd(NULL, 0), 1));
	if (!env_key("SHLVL", env))
		list_add_back(&env, new_env(ft_strdup("SHLVL"), ft_strdup("0"), 1));
}

t_env	*default_env(void)
{
	t_env	*env;

	env = new_env(ft_strdup("PWD"), getcwd(NULL, 0), 1);
	env->next = new_env(ft_strdup("SHLVL"), ft_strdup("0"), 1);
	env->next->next = new_env(ft_strdup("_"), ft_strdup("/usr/bin/env"), 1);
	env->next->next->next = new_env(ft_strdup("OLDPWD"), ft_strdup(""), 0);
	return (env);
}
