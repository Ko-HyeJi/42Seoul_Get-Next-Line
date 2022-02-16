/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:59:49 by hyko              #+#    #+#             */
/*   Updated: 2022/02/16 23:37:06 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*read_line;
	char		*return_line;
	int			cut_idx;

	cut_idx = find_newline(backup);
	while (cut_idx == -1)
	{	
		read_line = gnl_read(fd);
		if (read_line == NULL)
			break ;
		backup = ft_strjoin(backup, read_line);
		cut_idx = find_newline(backup);
	}
	if (cut_idx != -1)
	{
		return_line = ft_substr(backup, 0, cut_idx + 1);
		backup = ft_substr(backup, cut_idx + 1, ft_strlen(backup) - cut_idx - 1);
		return (return_line);
	}
	else
	{
		return (NULL);
	}
}

char	*gnl_read(int fd)
{
	char	*read_line;
	int		read_size;

	read_line = (char *)malloc(BUFFER_SIZE + 1);
	if (read_line == NULL)
	{
		free(read_line);
		return (NULL);
	}
	read_size = read(fd, read_line, BUFFER_SIZE);
	if (read_size == -1)
	{
		free(read_line);
		return (NULL);
	}
	read_line[read_size] = '\0';
	if (read_size < BUFFER_SIZE && read_size == 0)
		read_line = NULL;
	//printf("read_size : %d\n", read_size);
	//printf("read_line : %s\n", read_line);
	return (read_line);
}

int	find_newline(char *backup)
{
	int	idx;

	if (backup == NULL)
		return (-1);
	idx = 0;
	while (idx < (int)ft_strlen(backup))
	{
		if (backup[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}
