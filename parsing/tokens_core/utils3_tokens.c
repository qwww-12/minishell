/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:50:50 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 18:11:42 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_symbols_space(char c)
{
	if (is_symbols(c) || is_space(c))
		return (1);
	return (0);
}

void	flag_qt_hm(char *content, bool *qt, bool *hm)
{
	int		r;

	r = 0;
	if (content[r] == '~')
		*hm = 0;
	if (!content[r])
	{
		*qt = 1;
		return ;
	}
	while (content[r])
	{
		if (is_space(content[r]))
		{
			*qt = 1;
			break ;
		}
		r++;
	}
}

void	cut_value_quotes(int *r, char *tokens, char c, bool flag)
{
	*r = 1;
	while (tokens[*r])
	{
		if (tokens[*r] == c)
		{
			flag = 0;
			*r = *r + 1;
		}
		if (!flag && tokens[*r] && is_symbols_space(tokens[*r]))
			break ;
		if (!flag && (tokens[*r] == '\'' || tokens[*r] == '"') && tokens[*r])
		{
			flag = 1;
			c = tokens[*r];
			*r = *r + 1;
		}
		if (tokens[*r] && tokens[*r] != c)
			*r = *r + 1;
	}
}
