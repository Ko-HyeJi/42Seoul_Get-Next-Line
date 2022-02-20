/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:59:49 by hyko              #+#    #+#             */
/*   Updated: 2022/02/19 21:02:54 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*backup;
	//char		*read_line;
	char		*return_line;
	int			cut_idx;
	int			old_len;

	//if (fd < 0 || BUFFER_SIZE < 0)
	//	return (NULL);
	//return_line = NULL;
	//cut_idx = gnl_find_newline(backup); // gnl 함수가 호출되면 static 변수 backup에 개행이 있는지 확인
	//while (cut_idx == -1) // 개행이 존재하지 않으면...
	//{
	//	/* read_line = gnl_read_line(fd); // ***fd에서 BUFFER_SIZE만큼 읽어들임***
	//	if (read_line == NULL) // gnl_read 함수 실행 중 오류 발생
	//		break ;
	//	backup = ft_strjoin(backup, read_line); // ***읽어들인 라인을 backup뒤에 붙임*** */
	//	backup = gnl_expand_buffer(backup, fd); //새로운 라인을 읽어서 backup에 붙임
	//	cut_idx = gnl_find_newline(backup); // ***backup에 개행이 있는지 확인***
	//	if (backup == NULL)
	//		break ;
	//	if (backup[0] == 0)
	//		cut_idx = ft_strlen(backup);
	//	/*if (read_line[0] == 0 && backup[0] != 0) // read 함수가 읽은 값이 없지만 backup에 반환할 값이 남아있음
	//		cut_idx = ft_strlen(backup); // 개행을 찾을 수 없기 때문에 cut_idx를 문장 끝으로 지정
	//	if (read_line[0] == 0 && backup[0] == 0) // 반복문 종료
	//		break ;*/
	//	
	//}
	//if (cut_idx != -1)
	//{
	//	return_line = ft_substr(backup, 0, cut_idx + 1);
	//	backup = ft_substr(backup, cut_idx + 1, ft_strlen(backup) - cut_idx - 1);
	//	return (return_line);
	//}
	//else
	//	return (NULL);

	// **************************************************************************************

char	*gnl_shrink_buffer(char *backup, char *return_line)
{
	char	*new_backup;
	int		line_len;

	if (backup == NULL || return_line == NULL)
		return (NULL);
	line_len = ft_strlen(return_line);
	if ((int)ft_strlen(backup) == line_len)
	{
		free(backup);
		return (NULL);
	}
	new_backup = ft_substr(backup, line_len, ft_strlen(backup) - line_len);
	free(backup);
	return (new_backup);
}

char	*gnl_expand_buffer(char *backup, int fd)
{
	char	*new_backup;
	char	*read_line;

	read_line = gnl_read_line(fd);
	if (read_line == NULL) //gnl_read_line 함수에서 에러가 발생
		return (NULL);
	if (read_line[0] == 0) //read_size == 0 (더 이상 읽어들일 것이 없음)
	{
		free(read_line);
		return (backup);
	}
	if (backup == NULL)
		return (read_line);
	new_backup = ft_strjoin(backup, read_line);
	free(backup);
	free(read_line);
	return (new_backup);
}

char	*gnl_read_line(int fd)
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
	read_line[read_size] = '\0';
	return (read_line);
}

int	gnl_find_newline(char *backup) // 개행을 찾으면 첫번째 개행 인덱스 반환, 개행이 없으면 -1 반환
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
