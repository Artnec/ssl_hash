/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:14:37 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/24 15:14:38 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

char		*sha256(char *input, uint64_t size)
{
	t_md5			s;
	unsigned char	result[32];

	s.a = 0x6a09e667;
	s.b = 0xbb67ae85;
	s.c = 0x3c6ef372;
	s.d = 0xa54ff53a;
	s.e = 0x510e527f;
	s.f = 0x9b05688c;
	s.g = 0x1f83d9ab;
	s.h = 0x5be0cd19;
	s.low = 0;
	s.high = 0;
	sha256_update(&s, input, size);
	sha256_final(result, &s);
	return (get_result_string(result, 32));
}

char		*sha224(char *input, uint64_t size)
{
	t_md5			s;
	unsigned char	result[28];

	s.a = 0xc1059ed8;
	s.b = 0x367cd507;
	s.c = 0x3070dd17;
	s.d = 0xf70e5939;
	s.e = 0xffc00b31;
	s.f = 0x68581511;
	s.g = 0x64f98fa7;
	s.h = 0xbefa4fa4;
	s.low = 0;
	s.high = 0;
	sha256_update(&s, input, size);
	sha224_final(result, &s);
	return (get_result_string(result, 28));
}
