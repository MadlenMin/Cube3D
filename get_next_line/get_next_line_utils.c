/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:36:00 by szakarya          #+#    #+#             */
/*   Updated: 2025/03/19 18:36:04 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin_2(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			str[i++] = *s1++;
	if (s2)
		while (*s2)
			str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

void	*clean_storage(char *storage)
{
	if (storage)
		free(storage);
	return (NULL);
}

char	*keep_storage(char *storage)
{
	char	*res;
	char	*line;

	line = ft_strchr(storage, '\n');
	if (!line)
		return (clean_storage(storage));
	res = ft_strdup(line + 1);
	free(storage);
	return (res);
}

char	*extract_line(char *storage)
{
	char	*line;

	if (!storage || !*storage)
		return (NULL);
	line = ft_strchr(storage, '\n');
	if (!line || !*line)
		return (ft_substr(storage, 0, ft_strlen(storage)));
	return (ft_substr(storage, 0, line - storage + 1));
}

char	*read_file(int fd, char *storage)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*new_storage;

	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		new_storage = ft_strjoin_2(storage, buffer);
		free(storage);
		storage = new_storage;
		if (!storage)
			return (NULL);
	}
	if (bytes_read < 0)
		return (clean_storage(storage));
	return (storage);
}
