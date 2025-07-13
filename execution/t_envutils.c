/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:23:51 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/13 17:48:10 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_env *list)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	list_add_back(t_env **list, t_env *new)
{
	t_env	*tmp;

	if (!list)
		return ;
	if (!(*list))
	{
		(*list) = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*list_new_node(char *value, char *key, bool eq)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (eprintf(ERR_MEM), NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->eq = eq;
	new->next = NULL;
	return (new);
}

char	**environment_to_array(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	char	*join;
	int		len;
	int		r;

	r = 0;
	len = list_size(env);
	tmp = env;
	envp = malloc(sizeof (char *) * (len + 1));
	if (!envp)
		return (eprintf(ERR_MEM), NULL);
	while (tmp)
	{
		if (tmp->eq)
			join = ft_strjoin(tmp->key, "=");
		else
			join = ft_strdup(tmp->key);
		envp[r++] = ft_strjoin(join, tmp->value);
		p1char(&join);
		tmp = tmp->next;
	}
	envp[r] = NULL;
	return (envp);
}
