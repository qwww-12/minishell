/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:31:27 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/17 17:37:36 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*add_1shlvl(char *value)
{
	char	*newn;
	int		n;

	newn = NULL;
	n = ft_atoi(value);
	n += 1;
	newn = ft_itoa(n);
	p1char(&value);
	return (newn);
}
