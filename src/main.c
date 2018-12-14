/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:31:58 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/08 15:31:59 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

void		initiate_functions_array(t_ssl *s)
{
	s->commands_num = 8;
	s->commands[0] = "md5";
	s->commands[1] = "sha224";
	s->commands[2] = "sha256";
	s->commands[3] = "sha384";
	s->commands[4] = "sha512";
	s->commands[5] = "sha512/224";
	s->commands[6] = "sha512/256";
	s->commands[7] = "whirlpool";
	s->fun[0] = md5;
	s->fun[1] = sha224;
	s->fun[2] = sha256;
	s->fun[3] = sha384;
	s->fun[4] = sha512;
	s->fun[5] = sha512_224;
	s->fun[6] = sha512_256;
	s->fun[7] = whirlpool;
}

int			main(int argc, char **argv)
{
	t_ssl		s;

	setbuf(stdout, NULL);
	initiate_functions_array(&s);
	if (argc == 1)
		read_commands_from_stdin(&s);
	else
		parse_args(argv + 1, &s);
	return (0);
}
