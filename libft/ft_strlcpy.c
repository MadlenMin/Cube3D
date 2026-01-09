/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:29:27 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/26 13:29:28 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*(src + i))
		i++;
	if (size == 0)
		return (i);
	while (--size > 0 && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (i);
}
