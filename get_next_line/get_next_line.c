/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:35:26 by szakarya          #+#    #+#             */
/*   Updated: 2025/03/19 18:35:29 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	storage = read_file(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	if (!line)
		return (storage = clean_storage(storage));
	storage = keep_storage(storage);
	return (line);
}
