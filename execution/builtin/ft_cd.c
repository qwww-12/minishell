/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:21:03 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/19 18:46:41 by mbarhoun         ###   ########.fr       */
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

static void	old_path_output(int old, char *newpwd)
{
	if (old == 1)
	{
		if (newpwd)
		{
			e_status(0);
			write(1, newpwd, ft_strlen(newpwd));
			write(1, "\n", 1);
		}
		else
			error_cd_output("OLDPWD");
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
	e_status(0);
	return (1);
}

static int	path(t_env *env, char **newpwd, char **oldpwd, char *pwd)
{
	int		old;
	char	*tmp;

	old = 2;
	*oldpwd = getcwd(NULL, 0);
	if (pwd[0] == '-' && !pwd[1])
	{
		*newpwd = env_value("OLDPWD", env);
		old = 1;
	}
	else
		*newpwd = ft_strdup(pwd);
	if (chdir(*newpwd) == -1)
	{
		tmp = *newpwd;
		*newpwd = ft_strjoin("cd: ", tmp);
		p1char(&tmp);
		print_errno_info(*newpwd);
		e_status(1);
		p1char(oldpwd);
		p1char(newpwd);
		return (0);
	}
	return (old);
}

void	ft_cd(t_env *env, char **pwd, bool hm)
{
	char	*newpwd;
	char	*oldpwd;
	int		old;

	oldpwd = NULL;
	newpwd = NULL;
	old = 0;
	if (is_home(*pwd, hm))
	{
		if (!home_path(env, &newpwd, &oldpwd))
			return ;
	}
	else
	{
		if ((*pwd)[0] == '~' && (*pwd)[1] == '/' && hm)
			*pwd = change_to_home(env, pwd);
		old = path(env, &newpwd, &oldpwd, *pwd);
		if (!old)
			return ;
	}
	p1char(&newpwd);
	newpwd = getcwd(NULL, 0);
	old_path_output(old, newpwd);
	update_env_clean(env, &newpwd, &oldpwd);
}
