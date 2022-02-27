/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 22:00:27 by lprates           #+#    #+#             */
/*   Updated: 2021/09/25 20:18:49 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	*ft_realloc(void *src, size_t size)
{
	void	*dst;

	dst = malloc(size + 1);
	if (!dst)
	{
		free(src);
		return (NULL);
	}
	if (!src)
	{
		free(dst);
		return (NULL);
	}
	dst = ft_memmove(dst, src, size);
	free(src);
	src = NULL;
	return (dst);
}*/

void	*ft_realloc(void *ptr, size_t orig_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = 0;
	if (new_size == 0)
		free(ptr);
	else if (!ptr)
	{
		new_ptr = malloc(new_size);
		if (!new_ptr)
			return (0);
	}
	else if (new_size <= orig_size)
		return (ptr);
	else if (ptr && new_size > orig_size)
	{
		new_ptr = malloc(new_size);
		if (!new_ptr)
			return (0);
		ft_memcpy(new_ptr, ptr, orig_size);
		free(ptr);
	}
	return (new_ptr);
}