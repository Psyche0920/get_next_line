/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wehan <wehan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:03:21 by wehan             #+#    #+#             */
/*   Updated: 2025/10/30 20:03:43 by wehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//find the newline
static int	ft_newline(const char*s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

//split the buffer and store
static void	split_buffer_store(char *buffer, char *store)
{
	int		newline_pos;

	newline_pos = ft_newline(buffer);
	if (newline_pos >= 0)
	{
		if (newline_pos < (int)ft_strlen(buffer) - 1)
		{	
			ft_strlcpy(store, buffer + newline_pos + 1, BUFFER_SIZE + 1);
			buffer[newline_pos + 1] = '\0';
		}
		else
			store[0] = '\0';
	}
	else
		store[0] = '\0';
}

//read and append
static char	*read_and_append(char *buffer, int fd)
{
	int		bytes_read;
	char	*temp;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	bytes_read = 1;
	while (ft_newline(buffer) < 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
		free (temp);
		temp = (char *)malloc(BUFFER_SIZE + 1);
		if (!temp)
			return (free(buffer), NULL);
		if (!buffer)
			return (free(temp), NULL);
	}
	free(temp); 
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	store[BUFFER_SIZE + 1] = {0};

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = ft_strdup(store);
	if (!buffer)
		return (store[0] = '\0', NULL);
	buffer = read_and_append(buffer, fd);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		ft_bzero(store, BUFFER_SIZE + 1);
		return (NULL);
	}
	split_buffer_store(buffer, store);
	return (buffer);
}
