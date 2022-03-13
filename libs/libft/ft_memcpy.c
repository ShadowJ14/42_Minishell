/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:47:19 by lprates           #+#    #+#             */
/*   Updated: 2022/03/13 22:18:26 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	const unsigned char	*smemory;
	unsigned char		*dmemory;

	i = 0;
	smemory = src;
	dmemory = dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n && smemory[i])
	{
		dmemory[i] = smemory[i];
		i++;
	}
	return (dest);
}
