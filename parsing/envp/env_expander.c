/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:04:33 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/01 17:52:28 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*env_value(char *key, t_env *env)
{
	t_env	*tmp;
	char	*value;

	tmp = env;
	value = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		value = ft_strdup(tmp->value);
	return (value);
}

char	*key_not_found(char **content, int pos_key, int len_key)
{
	char	*value;
	int		r;
	int		f;

	r = -1;
	f = 0;
	value = malloc(sizeof(char) * (ft_strlen(*content) - len_key + 2));
	if (!value)
		return (NULL);
	while ((*content)[++r])
	{
		if (r == pos_key)
		{
			r += len_key;
			continue ;
		}
		value[f++] = (*content)[r];
	}
	value[f] = '\0';
	free(*content);
	return (value);
}

char	*key_value(char **content, char *v_env, int pos, int len_key)
{
	char	*value;
	int		r;
	int		g;
	int		f;

	r = -1;
	g = -1;
	f = 0;
	value = malloc(ft_strlen(*content) - len_key + ft_strlen(v_env) + 1);
	if (!value)
		return (NULL);
	while ((*content)[++r] && r < ft_strlen(*content))
	{
		if (r == pos)
		{
			while (v_env[++g])
				value[f++] = v_env[g];
			r += len_key - 1;
			continue ;
		}
		value[f++] = (*content)[r];
	}
	value[f] = '\0';
	free(*content);
	return (value);
}

static int	expand_var(char **content, t_ambg amb, t_env *env, bool f_quotes)
{
	t_exp	exp;

	set_var_exp(&exp.len_key, &exp.len_value, &exp.r, amb.r);
	if (is_special((*content)[exp.r], f_quotes))
		return (expand_meta(content, amb.r, exp.r, f_quotes));
	while ((*content)[exp.r] && is_valid_key((*content)[exp.r]))
		increment(&exp.r, &exp.len_key);
	exp.key = cdup(exp.len_key, *content + (amb.r + 1));
	exp.value = env_value(exp.key, env);
	if (!exp.value && (*content)[amb.r + 1] == '\'' && f_quotes)
		return (p1char(&exp.key), 1);
	if (!exp.value)
	{
		ambiguous_redirect(amb.ambiguous, exp.key);
		*content = key_not_found(content, amb.r, exp.len_key);
	}
	else
		*content = key_value(content, exp.value, amb.r, exp.len_key + 1);
	free(exp.key);
	if (exp.value)
	{
		exp.len_value = ft_strlen(exp.value);
		free(exp.value);
	}
	return (exp.len_value);
}

void	is_env(char **content, t_env *env, bool expander, bool ambg)
{
	t_ambg	amb;

	amb.d_quotes = 0;
	amb.s_quotes = 0;
	amb.ambiguous = ambg;
	amb.r = 0;
	while ((*content)[amb.r])
	{
		if ((*content)[amb.r] == '"' && amb.d_quotes)
			change_value(&amb.d_quotes, 0);
		else if ((*content)[amb.r] == '\'' && amb.s_quotes)
			change_value(&amb.s_quotes, 0);
		else if ((*content)[amb.r] == '"' && !amb.s_quotes)
			change_value(&amb.d_quotes, 1);
		else if ((*content)[amb.r] == '\'' && !amb.d_quotes)
			change_value(&amb.s_quotes, 1);
		else if ((*content)[amb.r] == '$' && !amb.s_quotes && expander)
		{
			amb.r += expand_var(content, amb, env, amb.d_quotes);
			continue ;
		}
		amb.r++;
	}
}
