/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:58:34 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/25 18:06:12 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	*allocate_memory(size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	return (new_ptr);
}

static void	copy_memory(void *dst, void *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
}

static size_t	get_copy_size(size_t old_size, size_t new_size)
{
	if (old_size < new_size)
		return (old_size);
	return (new_size);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = allocate_memory(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		copy_size = get_copy_size(old_size, new_size);
		copy_memory(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}
