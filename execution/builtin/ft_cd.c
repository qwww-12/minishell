/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:21:03 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/12 18:30:34 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	error_cd_output(char *path)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, " No such file or directory\n", 28);
	e_status(1);
}

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

static bool	home_path(t_env *env, char **newpwd, char **oldpwd)
{
	*newpwd = env_value("HOME", env);
	if (*newpwd)
		*oldpwd = getcwd(NULL, 0);
	if (chdir(*newpwd) == -1)
	{
		*newpwd = ft_strdup("HOME");
		error_cd_output(*newpwd);
		p1char(newpwd);
		p1char(oldpwd);
		return (0);
	}
	return (1);
}

static bool	path(char **newpwd, char **oldpwd, char *pwd)
{
	*oldpwd = getcwd(NULL, 0);
	*newpwd = ft_strdup(pwd);
	if (chdir(*newpwd) == -1)
	{
		error_cd_output(pwd);
		p1char(oldpwd);
		p1char(newpwd);
		return (0);
	}
	return (1);
}

void	ft_cd(t_env *env, char *pwd)
{
	char	*newpwd;
	char	*oldpwd;

	oldpwd = NULL;
	newpwd = NULL;
	if (!pwd || (pwd && pwd[0] == '~' && !pwd[1]) || (pwd && pwd[0] == '-' && pwd[1] == '-' && !pwd[2]))
	{
		if (!home_path(env, &newpwd, &oldpwd))
			return ;
	}
	else
		if ((!path(&newpwd, &oldpwd, pwd)))
			return ;
	p1char(&newpwd);
	newpwd = getcwd(NULL, 0);
	update_env(env, oldpwd, "OLDPWD");
	update_env(env, newpwd, "PWD");
	p1char(&oldpwd);
	p1char(&newpwd);
}
