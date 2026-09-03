/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masolet- <masolet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 01:42:53 by masolet-          #+#    #+#             */
/*   Updated: 2026/09/01 01:44:16 by masolet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ltoa_hexa_size(unsigned long long nb)
{
	int	nlen;

	nlen = 0;
	while (nb > 0)
	{
		nb /= 16;
		nlen++;
	}
	return (nlen);
}

char	*ft_ltoa_hexa(unsigned long long n, char format)
{
	size_t	nlen;
	char	*res;

	if (n == 0)
		return (ft_strdup("0"));
	nlen = ft_ltoa_hexa_size(n);
	res = ft_calloc((nlen + 1) * sizeof(char), 1);
	if (!res)
		return (NULL);
	res[nlen] = '\0';
	while (n > 0)
	{
		nlen--;
		res[nlen] = "0123456789abcdef"[(n % 16)];
		if (format == 'X' && (res[nlen] >= 'a' && res[nlen] <= 'f'))
			res[nlen] -= 32;
		n /= 16;
	}
	return (res);
}
