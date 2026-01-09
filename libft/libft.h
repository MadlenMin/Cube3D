/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:34 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/30 21:33:38 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

char		*ft_strdup(const char *s);
void		ft_putnbr(int nb);
char		*ft_strjoin(char *s1, char *s2, int should_free);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
char		**ft_split(char *s, char c);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_putnbr_fd(int n, int fd);

#endif