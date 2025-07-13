/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:19:22 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/13 18:00:51 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_path_output(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

static char	*get_path(char *path, char *cmd)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	tmp2 = tmp;
	tmp = ft_strjoin(tmp, cmd);
	p1char(&tmp2);
	return (tmp);
}

char	*find_path(t_env *env, char *cmd)
{
	char	*path;
	char	**all_path;
	int		r;

	path = env_value("PATH", env);
	if (!path)
		return (NULL);
	all_path = ft_split(path, ':');
	r = 0;
	p1char(&path);
	while (all_path[r])
	{
		path = get_path(all_path[r], cmd);
		if (access(path, X_OK) == 0)
			break ;
		p1char(&path);
		r++;
	}
	return (path);
}
