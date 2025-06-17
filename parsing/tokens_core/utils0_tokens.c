/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:06:24 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/01 11:57:00 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_value(int r, bool *f_quotes)
{
	*f_quotes = 0;
	return (r);
}

int	skip_space(char *str)
{
	int	r;

	r = 0;
	while (str[r] && is_space(str[r]))
		r++;
	return (r);
}

void	set_var_zero(int *v1, int *v2, bool *v3, t_token **lv4)
{
	*v1 = 0;
	*v2 = 0;
	*v3 = 0;
	*lv4 = NULL;
}

void	node_back(t_token **main, t_token *new)
{
	t_token	*tmp;

	if (!main || !*main || !new)
		return ;
	tmp = *main;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*create_node(char *content)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->content = content;
	node->red = 0;
	node->exp = 1;
	node->next = NULL;
	return (node);
}
