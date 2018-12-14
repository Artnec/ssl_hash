/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:42:32 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/12 19:42:33 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

static char		*get_longer_string(char *buf, int bufl, char *s, uint64_t sl)
{
	char *longer_str = (char *)malloc(sl + bufl + 1);

	uint64_t i = 0;
	for (; i < sl; i++)
		longer_str[i] = s[i];
	free(s);

	for (int n = 0; n < bufl; n++, i++)
		longer_str[i] = buf[n];
	longer_str[i] = '\0';
	return (longer_str);
}

static int		check_fd(int fd)
{
	char	buf[1];

	if (read(fd, buf, 0) < 0)
	{
		printf("error: cant read directory\n");
		return (1);
	}
	return (0);
}

char			*read_input(int fd, uint64_t *size)
{
	if (check_fd(fd))
		exit(1);

	char	buff[BUFF_SIZE];
	int		bytes_read;
	char	*input = NULL;
	*size = 0;
	while ((bytes_read = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (input == NULL)
		{
			input = (char *)malloc(bytes_read + 1);
			for (int i = 0; i < bytes_read; i++)
				input[i] = buff[i];
			input[bytes_read] = '\0';
		}
		else
			input = get_longer_string(buff, bytes_read, input, *size);
		*size += bytes_read;
	}
	return (input);
}
