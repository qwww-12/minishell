/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:26:09 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/21 17:33:26 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_eq(char *content)
{
	int		r;

	r = 0;
	while (content[r])
	{
		if (content[r] == '=')
			return (1);
		r++;
	}
	return (0);
}

char	*new_value_quotes(char *str)
{
	int		r;
	int		r1;
	char	strr[70000];

	r = -1;
	r1 = 0;
	while (str[++r])
	{
		if (str[r] == '"')
		{
			strr[r1++] = '\'';
			strr[r1++] = str[r];
			strr[r1++] = '\'';
		}
		if (str[r] == '\'')
		{
			strr[r1++] = '"';
			strr[r1++] = str[r];
			strr[r1++] = '"';
		}
		if (str[r] != '\'' && str[r] != '"')
			strr[r1++] = str[r];
	}
	strr[r1] = '\0';
	return (free(str), ft_strdup(strr));
}

void	remove_value_oldpwd(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			p1char(&env->value);
			env->value = ft_strdup("");
			env->eq = 0;
		}
		env = env->next;
	}
}

void	set_new_content(t_token **token, t_exp *exp, t_ambg *amb)
{
	if (count_word(exp->value) > 1 && amb->ambiguous)
	{
		(*token)->amb = 1;
		(*token)->type_token = AMB;
		return ;
	}
	(*token)->content = key_value(&(*token)->content, exp->value, \
						amb->r, exp->len_key + 1);
}
