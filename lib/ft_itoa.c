/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:51:37 by mbarhoun          #+#    #+#             */
/*   Updated: 2024/11/02 11:43:07 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(int n)
{
	int	b;

	b = 0;
	if (n == -2147483648)
		return (11);
	if (!n)
		return (1);
	if (n < 0)
	{
		b = 1;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		b++;
	}
	return (b);
}

char	*ft_itoa(int n)
{
	int		nlen;
	int		ngt;
	char	*ma;

	nlen = ft_nlen(n);
	ngt = 1;
	ma = (char *)malloc(sizeof(char) * (nlen + 1));
	if (!ma)
		return (NULL);
	if (n < 0)
	{
		ma[0] = '-';
		ngt = -1;
	}
	if (!n)
		ma[0] = '0';
	ma[nlen] = '\0';
	while (nlen-- && n)
	{
		ma[nlen] = (n % 10) * ngt + 48;
		n /= 10;
	}
	return (ma);
}
