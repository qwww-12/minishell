/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:26:09 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/02 21:44:47 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_new_content(char **content, t_exp *exp, t_ambg *amb)
{
	if (count_word(exp->value) > 1)
	{
		printf("minishell: $%s: ambiguous redirect\n", exp->key);
		*content = key_not_found(content, amb->r, exp->len_key);
		return ;
	}
	*content = key_value(content, exp->value, amb->r, exp->len_key + 1);
}
