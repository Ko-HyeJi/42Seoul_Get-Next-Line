/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:59:49 by hyko              #+#    #+#             */
/*   Updated: 2022/02/18 20:09:13 by hyko             ###   ########.fr       */
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

	if (fd < 0 || fd > 4095 || BUFFER_SIZE < 0)
		return (NULL);
	cut_idx = find_newline(backup);
	while (cut_idx == -1) //개행 X
	{
		read_line = gnl_read(fd);
		if (read_line == NULL)
		{
			free (read_line);
			break ;
		}
		backup = ft_strjoin(backup, read_line);
		cut_idx = find_newline(backup);
		if (read_line[0] == 0 && backup[0] != 0) // read 함수가 아무것도 읽어들이지 않았지만 backup에 반환할 값이 남아있음
		{
			cut_idx = ft_strlen(backup);
		}
		else if (read_line[0] == 0)
		{
			free (read_line);
			return (NULL);
		}
	}
	if (cut_idx != -1) //개행 O
	{
		return_line = ft_substr(backup, 0, cut_idx + 1); // 개행 앞 문자열 + 개행까지 복사
		backup = ft_substr(backup, cut_idx + 1, ft_strlen(backup) - cut_idx - 1); // 개행 뒤 문자열 복사
		return (return_line);
	}
	else
	{
		free(backup);
		return (NULL);
	}
}

char	*gnl_read(int fd)
{
	char	*read_line;
	int		read_size;

	read_line = (char *)malloc(BUFFER_SIZE + 1);
	if (read_line == NULL) //malloc 에러 처리
		return (NULL);
	read_size = read(fd, read_line, BUFFER_SIZE);
	if (read_size == -1) //read 에러 처리
	{
		free(read_line);
		return (NULL);
	}
	return (read_line);
}

int	find_newline(char *backup) // 개행을 찾으면 첫번째 개행 인덱스 반환, 개행이 없으면 -1 반환
{
	int	idx;
	int len;

	if (backup == NULL)
		return (-1);
	idx = 0;
	len = ft_strlen(backup);
	while (idx < len)
	{
		if (backup[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}
