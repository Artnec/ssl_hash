/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:14:45 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/24 15:14:47 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

char		*sha512(char *input, uint64_t size)
{
	t_md5			s;
	unsigned char	result[64];

	s.a = 0x6a09e667f3bcc908;
	s.b = 0xbb67ae8584caa73b;
	s.c = 0x3c6ef372fe94f82b;
	s.d = 0xa54ff53a5f1d36f1;
	s.e = 0x510e527fade682d1;
	s.f = 0x9b05688c2b3e6c1f;
	s.g = 0x1f83d9abfb41bd6b;
	s.h = 0x5be0cd19137e2179;
	s.low = 0;
	s.high = 0;
	sha512_update(&s, input, size);
	sha512_final(result, &s);
	return (get_result_string(result, 64));
}

char		*sha384(char *input, uint64_t size)
{
	t_md5			s;
	unsigned char	result[48];

	s.a = 0xcbbb9d5dc1059ed8;
	s.b = 0x629a292a367cd507;
	s.c = 0x9159015a3070dd17;
	s.d = 0x152fecd8f70e5939;
	s.e = 0x67332667ffc00b31;
	s.f = 0x8eb44a8768581511;
	s.g = 0xdb0c2e0d64f98fa7;
	s.h = 0x47b5481dbefa4fa4;
	s.low = 0;
	s.high = 0;
	sha512_update(&s, input, size);
	sha384_final(result, &s);
	return (get_result_string(result, 48));
}

char		*sha512_256(char *input, uint64_t size)
{
	t_md5			s;
	unsigned char	result[32];

	s.a = 0x22312194FC2BF72C;
	s.b = 0x9F555FA3C84C64C2;
	s.c = 0x2393B86B6F53B151;
	s.d = 0x963877195940EABD;
	s.e = 0x96283EE2A88EFFE3;
	s.f = 0xBE5E1E2553863992;
	s.g = 0x2B0199FC2C85B8AA;
	s.h = 0x0EB72DDC81C52CA2;
	s.low = 0;
	s.high = 0;
	sha512_update(&s, input, size);
	sha512_256_final(result, &s);
	return (get_result_string(result, 32));
}

char		*sha512_224(char *input, uint64_t size)
{
	t_md5			s;
	unsigned char	result[28];

	s.a = 0x8C3D37C819544DA2;
	s.b = 0x73E1996689DCD4D6;
	s.c = 0x1DFAB7AE32FF9C82;
	s.d = 0x679DD514582F9FCF;
	s.e = 0x0F6D2B697BD44DA8;
	s.f = 0x77E36F7304C48942;
	s.g = 0x3F9D85A86A1D36C8;
	s.h = 0x1112E6AD91D692A1;
	s.low = 0;
	s.high = 0;
	sha512_update(&s, input, size);
	sha512_224_final(result, &s);
	return (get_result_string(result, 28));
}
