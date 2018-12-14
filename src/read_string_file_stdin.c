/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_string_file_stdin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 18:04:47 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/26 18:04:49 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

void	read_string(char *str, char *alg, t_ssl *s)
{
	s->in_flag = 1;
	if (str == NULL)
	{
		printf("option requires an argument -- s\n");
		printf("usage: %s [-qrp] [-s string] [files ...]\n", alg);
		exit(1);
	}
	else
	{
		char *hash = s->fun[s->com](str, strlen(str));
		if (s->q_flag == 0 && s->r_flag == 0)
			printf("%s (\"%s\") = %s\n", alg, str, hash);
		else if (s->q_flag == 1)
			printf("%s\n", hash);
		else if (s->r_flag == 1)
			printf("%s  \"%s\"\n", hash, str);
		free(hash);
	}
}

void	read_file(char *alg, char *file_name, t_ssl *s)
{
	s->in_flag = 1;
	int fd = open(file_name, O_RDONLY);
	if (fd == -1)
		printf("%s: %s: No such file or directory\n", alg, file_name);
	else if (read(fd, &fd, 0) == -1)
		printf("%s: %s: Is a directory\n", alg, file_name);
	else
	{
		uint64_t size;
		char *input = read_input(fd, &size);
		char *hash = s->fun[s->com](input, size);
		if (s->q_flag == 0 && s->r_flag == 0)
			printf("%s (%s) = %s\n", alg, file_name, hash);
		else if (s->q_flag == 1)
			printf("%s\n", hash);
		else if (s->r_flag == 1)
			printf("%s  %s\n", hash, file_name);
		free(input);
		free(hash);
	}
	close(fd);
}

void	read_stdin(t_ssl *s)
{
	uint64_t size;
	char *input = read_input(0, &size);
	char *hash = s->fun[s->com](input, size);
	if (s->in_flag == 1)
		printf("%s%s\n", input == NULL ? "" : input, hash);
	else
		printf("%s\n", hash);
	free(hash);
	free(input);
}
