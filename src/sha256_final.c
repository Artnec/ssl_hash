/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:56 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:57 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

void		sha256_final(unsigned char *result, t_md5 *s)
{
	uint64_t used = s->low & 0x3f;
	s->buffer[used++] = 0x80;
	uint64_t available = 64 - used;
	if (available < 8)
	{
		memset(&s->buffer[used], 0, available);
		sha256_transform(s, s->buffer, 64);
		used = 0;
		available = 64;
	}
	memset(&s->buffer[used], 0, available - 8);
	u32_to_chars_reverse_endian(&s->buffer[60], s->low * 8);
	u32_to_chars_reverse_endian(&s->buffer[56], s->high);
	sha256_transform(s, s->buffer, 64);
	u32_to_chars_reverse_endian(&result[0], s->a);
	u32_to_chars_reverse_endian(&result[4], s->b);
	u32_to_chars_reverse_endian(&result[8], s->c);
	u32_to_chars_reverse_endian(&result[12], s->d);
	u32_to_chars_reverse_endian(&result[16], s->e);
	u32_to_chars_reverse_endian(&result[20], s->f);
	u32_to_chars_reverse_endian(&result[24], s->g);
	u32_to_chars_reverse_endian(&result[28], s->h);
}

void		sha224_final(unsigned char *result, t_md5 *s)
{
	uint64_t used = s->low & 0x3f;
	s->buffer[used++] = 0x80;
	uint64_t available = 64 - used;
	if (available < 8)
	{
		memset(&s->buffer[used], 0, available);
		sha256_transform(s, s->buffer, 64);
		used = 0;
		available = 64;
	}
	memset(&s->buffer[used], 0, available - 8);
	u32_to_chars_reverse_endian(&s->buffer[60], s->low * 8);
	u32_to_chars_reverse_endian(&s->buffer[56], s->high);
	sha256_transform(s, s->buffer, 64);
	u32_to_chars_reverse_endian(&result[0], s->a);
	u32_to_chars_reverse_endian(&result[4], s->b);
	u32_to_chars_reverse_endian(&result[8], s->c);
	u32_to_chars_reverse_endian(&result[12], s->d);
	u32_to_chars_reverse_endian(&result[16], s->e);
	u32_to_chars_reverse_endian(&result[20], s->f);
	u32_to_chars_reverse_endian(&result[24], s->g);
}
