/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:17:43 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/01 18:04:56 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	search_space(char *content)
{
	int	r;

	r = -1;
	while (content[++r])
		if (is_space(content[r]))
			return (1);
	return (0);
}

static int	expand_var1(char **content, int pos, t_env *env)
{
	t_exp	exp;

	set_var_exp(&exp.len_key, &exp.len_value, &exp.r, pos);
	while ((*content)[exp.r] && is_valid_key((*content)[exp.r]))
		increment(&exp.r, &exp.len_key);
	exp.key = cdup(exp.len_key, *content + (pos + 1));
	exp.value = env_value(exp.key, env);
	if (!exp.value)
		return (free(exp.key), 1);
	if (search_space(exp.value))
		*content = key_value(content, exp.value, pos, exp.len_key + 1);
	free(exp.key);
	if (exp.value)
	{
		exp.len_value = ft_strlen(exp.value);
		free(exp.value);
	}
	return (exp.len_value);
}

void	env_space(char **input, t_env *env)
{
	bool	d_quotes;
	bool	s_quotes;
	int		r;

	d_quotes = 0;
	s_quotes = 0;
	r = 0;
	while ((*input)[r])
	{
		if ((*input)[r] == '"' && d_quotes)
			d_quotes = 0;
		else if ((*input)[r] == '\'' && s_quotes)
			s_quotes = 0;
		else if ((*input)[r] == '"' && !s_quotes)
			d_quotes = 1;
		else if ((*input)[r] == '\'' && !d_quotes)
			s_quotes = 1;
		if ((*input)[r] == '$' && !s_quotes && !d_quotes)
		{
			r += expand_var1(input, r, env);
			continue ;
		}
		r++;
	}
}
