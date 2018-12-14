/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_whirlpool_final.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:26:37 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/25 19:26:38 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

static void	u32_to_chars(unsigned char *str, uint32_t num)
{
	str[0] = (unsigned char)num;
	str[1] = (unsigned char)(num >> 8);
	str[2] = (unsigned char)(num >> 16);
	str[3] = (unsigned char)(num >> 24);
}

void		u32_to_chars_reverse_endian(unsigned char *str, uint32_t n)
{
	str[0] = (unsigned char)(n >> 24);
	str[1] = (unsigned char)(n >> 16);
	str[2] = (unsigned char)(n >> 8);
	str[3] = (unsigned char)n;
}

void		u64_to_chars_reverse_endian(unsigned char *str, uint64_t n)
{
	str[0] = (unsigned char)(n >> 56);
	str[1] = (unsigned char)(n >> 48);
	str[2] = (unsigned char)(n >> 40);
	str[3] = (unsigned char)(n >> 32);
	str[4] = (unsigned char)(n >> 24);
	str[5] = (unsigned char)(n >> 16);
	str[6] = (unsigned char)(n >> 8);
	str[7] = (unsigned char)n;
}

void		md5_final(unsigned char *result, t_md5 *s)
{
	uint64_t used = s->low & 0x3f;
	s->buffer[used++] = 0x80;
	uint64_t available = 64 - used;
	if (available < 8)
	{
		memset(&s->buffer[used], 0, available);
		md5_transform(s, s->buffer, 64);
		used = 0;
		available = 64;
	}
	memset(&s->buffer[used], 0, available - 8);
	u32_to_chars(&s->buffer[56], s->low * 8);
	u32_to_chars(&s->buffer[60], s->high);
	md5_transform(s, s->buffer, 64);
	u32_to_chars(&result[0], s->a);
	u32_to_chars(&result[4], s->b);
	u32_to_chars(&result[8], s->c);
	u32_to_chars(&result[12], s->d);
}

void		whirlpool_final(unsigned char *result, t_md5 *s)
{
	uint64_t used = s->low & 0x3f;
	s->buffer[used++] = 0x80;
	uint64_t available = 64 - used;
	if (available < 32)
	{
		memset(&s->buffer[used], 0, available);
		whirlpool_transform(s->hash, (uint64_t *)s->buffer, 64);
		used = 0;
		available = 64;
	}
	memset(&s->buffer[used], 0, available - 16);
	u64_to_chars_reverse_endian(&s->buffer[56], s->low * 8);
	u64_to_chars_reverse_endian(&s->buffer[48], s->high);
	whirlpool_transform(s->hash, (uint64_t *)s->buffer, 64);
	u64_to_chars_reverse_endian(&result[0], s->hash[0]);
	u64_to_chars_reverse_endian(&result[8], s->hash[1]);
	u64_to_chars_reverse_endian(&result[16], s->hash[2]);
	u64_to_chars_reverse_endian(&result[24], s->hash[3]);
	u64_to_chars_reverse_endian(&result[32], s->hash[4]);
	u64_to_chars_reverse_endian(&result[40], s->hash[5]);
	u64_to_chars_reverse_endian(&result[48], s->hash[6]);
	u64_to_chars_reverse_endian(&result[56], s->hash[7]);
}
