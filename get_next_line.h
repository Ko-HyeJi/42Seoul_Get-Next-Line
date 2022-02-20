/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:00:30 by hyko              #+#    #+#             */
/*   Updated: 2022/02/19 20:13:50 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 42

# endif

char	*get_next_line(int fd);
char	*gnl_read_line(int fd);
int		gnl_find_newline(char *read_line);

size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dest, char *src);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const	*s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

char	*gnl_expand_buffer(char *backup, int fd);
char	*gnl_shrink_buffer(char *backup, char *return_line);

#endif