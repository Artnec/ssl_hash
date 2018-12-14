/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:32:06 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/24 15:32:07 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

void		sha512_final(unsigned char *result, t_md5 *s)
{
	uint64_t used = s->low & 0x7f;
	s->buffer[used++] = 0x80;
	uint64_t available = 128 - used;
	if (available < 16)
	{
		memset(&s->buffer[used], 0, available);
		sha512_transform(s, s->buffer, 128);
		used = 0;
		available = 128;
	}
	memset(&s->buffer[used], 0, available - 16);
	u64_to_chars_reverse_endian(&s->buffer[120], s->low * 8);
	u64_to_chars_reverse_endian(&s->buffer[112], s->high);
	sha512_transform(s, s->buffer, 128);
	u64_to_chars_reverse_endian(&result[0], s->a);
	u64_to_chars_reverse_endian(&result[8], s->b);
	u64_to_chars_reverse_endian(&result[16], s->c);
	u64_to_chars_reverse_endian(&result[24], s->d);
	u64_to_chars_reverse_endian(&result[32], s->e);
	u64_to_chars_reverse_endian(&result[40], s->f);
	u64_to_chars_reverse_endian(&result[48], s->g);
	u64_to_chars_reverse_endian(&result[56], s->h);
}

void		sha384_final(unsigned char *result, t_md5 *s)
{
	uint64_t used = s->low & 0x7f;
	s->buffer[used++] = 0x80;
	uint64_t available = 128 - used;
	if (available < 16)
	{
		memset(&s->buffer[used], 0, available);
		sha512_transform(s, s->buffer, 128);
		used = 0;
		available = 128;
	}
	memset(&s->buffer[used], 0, available - 16);
	u64_to_chars_reverse_endian(&s->buffer[120], s->low * 8);
	u64_to_chars_reverse_endian(&s->buffer[112], s->high);
	sha512_transform(s, s->buffer, 128);
	u64_to_chars_reverse_endian(&result[0], s->a);
	u64_to_chars_reverse_endian(&result[8], s->b);
	u64_to_chars_reverse_endian(&result[16], s->c);
	u64_to_chars_reverse_endian(&result[24], s->d);
	u64_to_chars_reverse_endian(&result[32], s->e);
	u64_to_chars_reverse_endian(&result[40], s->f);
}

void		sha512_256_final(unsigned char *result, t_md5 *s)
{
	uint64_t used = s->low & 0x7f;
	s->buffer[used++] = 0x80;
	uint64_t available = 128 - used;
	if (available < 16)
	{
		memset(&s->buffer[used], 0, available);
		sha512_transform(s, s->buffer, 128);
		used = 0;
		available = 128;
	}
	memset(&s->buffer[used], 0, available - 16);
	u64_to_chars_reverse_endian(&s->buffer[120], s->low * 8);
	u64_to_chars_reverse_endian(&s->buffer[112], s->high);
	sha512_transform(s, s->buffer, 128);
	u64_to_chars_reverse_endian(&result[0], s->a);
	u64_to_chars_reverse_endian(&result[8], s->b);
	u64_to_chars_reverse_endian(&result[16], s->c);
	u64_to_chars_reverse_endian(&result[24], s->d);
}

void		sha512_224_final(unsigned char *result, t_md5 *s)
{
	uint64_t used = s->low & 0x7f;
	s->buffer[used++] = 0x80;
	uint64_t available = 128 - used;
	if (available < 16)
	{
		memset(&s->buffer[used], 0, available);
		sha512_transform(s, s->buffer, 128);
		used = 0;
		available = 128;
	}
	memset(&s->buffer[used], 0, available - 16);
	u64_to_chars_reverse_endian(&s->buffer[120], s->low * 8);
	u64_to_chars_reverse_endian(&s->buffer[112], s->high);
	sha512_transform(s, s->buffer, 128);
	u64_to_chars_reverse_endian(&result[0], s->a);
	u64_to_chars_reverse_endian(&result[8], s->b);
	u64_to_chars_reverse_endian(&result[16], s->c);
	u32_to_chars_reverse_endian(&result[24], s->d >> 32);
}
