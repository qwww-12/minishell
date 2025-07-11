/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:24:48 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/11 18:23:11 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_valide_key(char *str)
{
	int		r;
	char	*key;

	r = 0;
	if (str[r] != '_' && !ft_isalpha(str[r]))
		return (NULL);
	while (str[r] && (ft_isalnum(str[r]) || str[r] == '_'))
		r++;
	key = ft_substr(str, 0, r);
	if (!key)
		return (NULL);
	return (key);
}

void	desplay_list_export(t_env *env)
{
	while (env)
	{
		if (env->eq)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

t_env	*ft_copy_env(t_env *env)
{
	t_env	*list;
	t_env	*new;

	new = NULL;
	list = env;
	while (list)
	{
		list_add_back(&new, list_new_node(list->value, list->key, list->eq));
		list = list->next;
	}
	return (new);
}

void	swap_nodes(t_env *node1, t_env *node2)
{
	char	*temp_key;
	char	*temp_value;
	bool	temp_eq;

	if (!node1 || !node2)
		return ;
	temp_key = node1->key;
	node1->key = node2->key;
	node2->key = temp_key;
	temp_value = node1->value;
	node1->value = node2->value;
	node2->value = temp_value;
	temp_eq = node1->eq;
	node1->eq = node2->eq;
	node2->eq = temp_eq;
}
