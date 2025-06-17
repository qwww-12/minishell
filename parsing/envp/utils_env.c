/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:56:57 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/01 09:35:08 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_valid_key(char c)
{
	bool	r;

	r = 1;
	r *= (ft_isalnum(c) || c == '_') && c != '$';
	return (r);
}

void	set_var_exp(int *v1, int *v2, int *v3, int v4)
{
	*v1 = 0;
	*v2 = 0;
	*v3 = v4 + 1;
}

void	change_value(bool *quotes, int value)
{
	*quotes = value;
}

void	increment(int *v1, int *v2)
{
	*v1 += 1;
	*v2 += 1;
}

char	*cdup(int size, char *content)
{
	char	*dup;
	int		r;

	r = -1;
	dup = malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	while (content[++r] && r < size)
		dup[r] = content[r];
	dup[r] = '\0';
	return (dup);
}
