/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:41:46 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/12 15:58:08 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
