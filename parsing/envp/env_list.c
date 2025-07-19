/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:38:17 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/19 18:18:31 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	env_count(char **env)
{
	int	r;

	r = 0;
	while (env[r])
		r++;
	return (r);
}

static char	*get_env_key(char *env)
{
	char	*key;
	int		r;

	r = 0;
	while (env[r] && env[r] != '=')
		r++;
	key = malloc(sizeof(char) * (r + 1));
	if (!key)
		return (eprintf(ERR_MEM), NULL);
	r = 0;
	while (*env && *env != '=')
		key[r++] = *env++;
	key[r] = '\0';
	return (key);
}

static char	*get_env_value(char *env)
{
	char	*value;
	int		r;
	int		len;

	r = 0;
	len = 0;
	while (env[r] && env[r] != '=')
		r++;
	r++;
	while (env[r + len])
		len++;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (eprintf(ERR_MEM), NULL);
	len = 0;
	while (env[r])
		value[len++] = env[r++];
	value[len] = '\0';
	return (value);
}

t_env	*new_env(char *key, char *value, bool eq)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (eprintf(ERR_MEM), NULL);
	env->key = key;
	if (!ft_strcmp(env->key, "SHLVL"))
		env->value = add_1shlvl(value);
	else
		env->value = value;
	env->eq = eq;
	env->next = NULL;
	return (env);
}

t_env	*construct_env(char **ev, bool first)
{
	t_env	*env;
	t_env	*new;
	t_env	*tmp;
	int		r;
	int		counter;

	if (!ev || !*ev)
		return (default_env());
	env = new_env(get_env_key(ev[0]), get_env_value(ev[0]), is_eq(ev[0]));
	if (!env)
		return (NULL);
	tmp = env;
	counter = env_count(ev);
	r = 0;
	while (++r < counter)
	{
		new = new_env(get_env_key(ev[r]), get_env_value(ev[r]), is_eq(ev[r]));
		if (!new)
			return (env_leaks(env), eprintf(ERR_MEM), NULL);
		tmp->next = new;
		tmp = new;
	}
	if (first)
		remove_value_oldpwd(env);
	return (add_default_env(env), env);
}
