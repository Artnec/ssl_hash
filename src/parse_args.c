/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 17:58:08 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/26 17:58:09 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

static int		cmp(char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == *b);
}

static int		is_command(char *command, t_ssl *s)
{
	s->com = -1;
	if (command != NULL)
	{
		for (int n = 0; n < s->commands_num; n++)
		{
			if (cmp(command, s->commands[n]))
			{
				s->com = n;
				break ;
			}
		}
	}
	if (s->com == -1)
	{
		printf("\nft_ssl:Error: '%s' is an invalid command.\n\n", command);
		printf("Standard commands:\n\n");
		printf("Message Digest commands:\n%-18s%-18s", "md5", "sha224");
		printf("%-18s%-18s\n%-18s%-18s%-18s%-18s\n\n", "sha256", "sha384",
			"sha512", "sha512/224", "sha512/256", "whirlpool");
		printf("Cipher commands:\n\n");
		return (1);
	}
	return (0);
}

static int		initiate_and_check_command(char *command, t_ssl *s)
{
	s->r_flag = 0;
	s->q_flag = 0;
	s->in_flag = 0;
	return (is_command(command, s));
}

static int		parse_qr_flags(char **arg, t_ssl *s)
{
	int i = 1;
	if (cmp(*arg, "-q") || cmp(*arg, "-qs"))
	{
		s->q_flag = 1;
		i += 1;
	}
	else if (cmp(*arg, "-r") || cmp(*arg, "-rs"))
	{
		s->r_flag = 1;
		i += 1;
	}
	else if (cmp(*arg, "-qr") || cmp(*arg, "-rq")
		|| cmp(*arg, "-qrs") || cmp(*arg, "-rqs"))
	{
		s->q_flag = 1;
		i += 2;
	}
	return (i);
}

void			parse_args(char **argv, t_ssl *s)
{
	if (initiate_and_check_command(argv[0], s))
		return ;
	for (int n = 1; argv[n] != NULL; n++)
	{
		if (argv[n][0] == '-' && argv[n][1])
		{
			int i = parse_qr_flags(&argv[n], s);
			if (cmp(argv[n], "-p") && (s->in_flag = 1))
				read_stdin(s);
			else if (cmp(argv[n] + i, "s"))
				read_string(argv[++n], argv[0], s);
			else if (argv[n][i] != '\0')
			{
				printf("unknown option '-%c'\n", argv[n][i]);
				printf("usage: %s [-qrp] [-s string] [files ..]\n", argv[0]);
				exit(1);
			}
		}
		else
			read_file(argv[0], argv[n], s);
	}
	if (s->in_flag == 0)
		read_stdin(s);
}
