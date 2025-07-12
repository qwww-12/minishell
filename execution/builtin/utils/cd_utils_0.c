/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:53:09 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/12 21:18:33 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	update_env(t_env *env, char *new_value, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (env->value)
				p1char(&env->value);
			env->value = ft_strdup(new_value);
			env->eq = 1;
		}
		env = env->next;
	}
}

bool	is_home(char *pwd)
{
	return ((!pwd || (pwd && pwd[0] == '~' && !pwd[1]) 
			|| (pwd && pwd[0] == '-' && pwd[1] == '-' && !pwd[2]))
			|| (pwd && !pwd[0]));
}

void	update_env_clean(t_env *env, char **newpwd, char **oldpwd)
{
	update_env(env, *oldpwd, "OLDPWD");
	update_env(env, *newpwd, "PWD");
	p1char(oldpwd);
	p1char(newpwd);
}
