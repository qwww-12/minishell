/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:10:35 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/11 19:11:07 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_export_list(t_env **env, char *value, char *key, bool eq)
{
	t_env	*tmp;
	int		exist;

	exist = 0;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			exist = 1;
			if (eq)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strdup(value);
				tmp->eq = eq;
				return ;
			}
		}
		tmp = tmp->next;
	}
	if (!exist)
		list_add_back(env, list_new_node(value, key, eq));
}

static void	sort_export(t_env *var)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*small;

	new = NULL;
	new = ft_copy_env(var);
	tmp = new;
	while (tmp)
	{
		small = tmp;
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp2->key, small->key) < 0)
				small = tmp2;
			tmp2 = tmp2->next;
		}
		if (small != tmp)
			swap_nodes(small, tmp);
		tmp = tmp->next;
	}
	desplay_list_export(new);
	env_leaks(new);
}

static char	*parss_value(char *str, bool *eq)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		value = ft_strdup(str + i + 1);
		*eq = true;
	}
	else
		value = ft_strdup(str + i);
	return (value);
}

static int	export_new(char *str, t_env *env)
{
	bool	eq;
	char	*value;
	char	*key;

	eq = false;
	value = parss_value(str, &eq);
	key = get_valide_key(str);
	if (!key)
	{
		free(value);
		printf("minishell: export: `%s': not a valid identifier\n", str);
		e_status(1);
		return (1);
	}
	add_export_list(&env, value, key, eq);
	p1char(&value);
	p1char(&key);
	return (0);
}

void	ft_export(t_env *env, char **cmd)
{
	int		r;

	r = 1;
	if (!cmd[r])
	{
		sort_export(env);
		return ;
	}
	while (cmd[r])
	{
		export_new(cmd[r], env);
		r++;
	}
}
