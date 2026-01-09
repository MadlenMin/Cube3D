/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:35:34 by szakarya          #+#    #+#             */
/*   Updated: 2025/03/19 18:35:36 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

char	*get_next_line(int fd);
void	*clean_storage(char *storage);
char	*keep_storage(char *storage);
char	*extract_line(char *storage);
char	*read_file(int fd, char *storage);

#endif
