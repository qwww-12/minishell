/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:47:26 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/12 15:01:35 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static bool	ft_checkovf(long long ma, int mg, char c)
{
	if ((ma >= 922337203685477580 && mg == 1 && c >= '8') 
		|| (ma >= 922337203685477580 && mg == -1 && c >= '9'))
		return (0);
	return (1);
}

bool	is_overflow(const char *str, size_t *ma)
{
	int		mg;

	*ma = 0;
	mg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			mg = -1;
	while (*str >= 48 && *str <= 57)
	{
		if (!ft_checkovf(*ma, mg, *str))
			return (0);
		*ma = (*ma * 10) + (*str++ - 48);
	}
	*ma = *ma * mg;
	return (1);
}
