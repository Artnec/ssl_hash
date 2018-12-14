/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_whirlpool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:26:51 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/25 19:26:52 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

char		*whirlpool(char *input, uint64_t size)
{
	t_md5			s;
	unsigned char	result[64];

	s.low = 0;
	s.high = 0;
	memset(s.hash, 0, sizeof(s.hash));
	whirlpool_update(&s, input, size);
	whirlpool_final(result, &s);
	return (get_result_string(result, 64));
}

char		*md5(char *input, uint64_t size)
{
	t_md5			s;
	unsigned char	result[16];

	s.a = 0x67452301;
	s.b = 0xefcdab89;
	s.c = 0x98badcfe;
	s.d = 0x10325476;
	s.low = 0;
	s.high = 0;
	md5_update(&s, input, size);
	md5_final(result, &s);
	return (get_result_string(result, 16));
}
