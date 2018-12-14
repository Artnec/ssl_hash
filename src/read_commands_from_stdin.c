/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands_from_stdin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:38:34 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/12 19:38:35 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

static int		get_words_count(char *str)
{
	int num = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] > ' ' && str[i] < 127
		&& (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
			num++;
	}
	return (num);
}

static char		**split(char *str)
{
	int words_count = get_words_count(str);
	char **s = (char **)malloc(sizeof(char *) * (words_count + 1));
	for (int i = 0, n = 0; n < words_count; n++)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		int j = 0;
		while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\t')
			j++;
		s[n] = (char *)malloc(j + 1);
		j = 0;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			s[n][j++] = str[i++];
		s[n][j] = '\0';
	}
	s[words_count] = NULL;
	return (s);
}

void			read_commands_from_stdin(t_ssl *s)
{
	char	buff[32768];

	while (42)
	{
		printf("ssl_hash> ");
		int	bytes_read;
		if ((bytes_read = read(0, buff, 32768)) == 32768)
		{
			printf("error: argument size is too big\n");
			exit(1);
		}
		if (bytes_read == 0)
			break ;
		if (buff[0] == '\n')
			continue ;
		buff[bytes_read - (buff[bytes_read - 1] == '\n' ? 1 : 0)] = '\0';
		char **args = split(buff);
		parse_args(args, s);
		int i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
	}
}
