/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_special.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:37:36 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/01 16:53:23 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_expempty(char c)
{
	if (c == '@' || c == '*')
		return (1);
	return (0);
}

void	ambiguous_redirect(bool amb, char *key)
{
	if (amb)
		printf("minishell: $%s: ambiguous redirect\n", key);
}

bool	is_special(char c, bool f_quotes)
{
	if ((!ft_isalpha(c) && c != '\'' && c != '"' && c != '_') \
		|| (c == '"' && f_quotes))
		return (1);
	return (0);
}

int	expand_meta(char **content, int pos, int r, bool f_quotes)
{
	int		ival;
	char	*sval;

	sval = NULL;
	if ((*content)[r] == '\0' || ((*content)[r] == '"' && f_quotes))
		return (1);
	if ((*content)[r] == '0')
		return (*content = key_value(content, "minishell", pos, 2), \
				ft_strlen("minishell"));
	if (ft_isdigit((*content)[r]) || is_expempty((*content)[r]))
		return (*content = key_not_found(content, pos, 1), 0);
	if ((*content)[r] == '?')
	{
		ival = exit_status(-1);
		sval = ft_itoa(ival);
		return (*content = key_value(content, sval, pos, 2), \
				p1char(&sval), ft_strlen("0"));
	}
	return (1);
}
