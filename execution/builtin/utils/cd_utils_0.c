/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:53:09 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/19 18:19:54 by mbarhoun         ###   ########.fr       */
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

bool	is_home(char *pwd, bool hm)
{
	if (pwd[0] == '~' && !hm)
		return (0);
	return (((!pwd || (pwd && pwd[0] == '~' && !pwd[1]) 
				|| (pwd && pwd[0] == '-' && pwd[1] == '-' && !pwd[2]))
			|| (pwd && !pwd[0])));
}

void	update_env_clean(t_env *env, char **newpwd, char **oldpwd)
{
	update_env(env, *oldpwd, "OLDPWD");
	update_env(env, *newpwd, "PWD");
	p1char(oldpwd);
	p1char(newpwd);
}

char	*change_to_home(t_env *env, char **pwd)
{
	char	*new;
	char	*home;
	char	*tmp;
	int		v;

	v = 0;
	home = env_value("HOME", env);
	tmp = *pwd;
	*pwd = malloc(ft_strlen(tmp));
	if (!*pwd)
		return (eprintf(ERR_MEM), NULL);
	while (tmp[v + 1])
	{
		(*pwd)[v] = tmp[v + 1];
		v++;
	}
	p1char(&tmp);
	new = ft_strjoin(home, *pwd);
	p1char(pwd);
	p1char(&home);
	return (new);
}
