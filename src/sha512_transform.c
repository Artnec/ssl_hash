/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 20:05:21 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/23 20:05:22 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

#define ROTR(x, n)		((x >> n) | (x << (64 - n)))
#define SHR(x, n)		(x >> n)

#define E0(x)			(ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39))
#define E1(x)			(ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41))
#define O0(x)			(ROTR(x, 1) ^ ROTR(x, 8) ^ SHR(x, 7))
#define O1(x)			(ROTR(x, 19) ^ ROTR(x, 61) ^ SHR(x, 6))
#define CH(x, y, z)		((x & y) ^ (~x & z))
#define MAJ(x, y, z)	((x & y) ^ (x & z) ^ (y & z))

extern const uint64_t g_k512[80];

static void	set_msg_schedule_words(uint64_t *w, const unsigned char *ptr)
{
	int i = 0;
	while (i < 16)
	{
		w[i] = (uint64_t)ptr[0] << 56 | (uint64_t)ptr[1] << 48 |
		(uint64_t)ptr[2] << 40 | (uint64_t)ptr[3] << 32 |
		(uint64_t)ptr[4] << 24 | ptr[5] << 16 | ptr[6] << 8 | ptr[7];
		ptr += 8;
		i++;
	}
	while (i < 80)
	{
		w[i] = O1(w[i - 2]) + w[i - 7] + O0(w[i - 15]) + w[i - 16];
		i++;
	}
}

static void	loop(uint64_t *words, uint64_t *w)
{
	for (int n = 0; n < 80; n++)
	{
		uint64_t tmp1 = words[7] + E1(words[4]) +
		CH(words[4], words[5], words[6]) + g_k512[n] + w[n];
		uint64_t tmp2 = E0(words[0]) + MAJ(words[0], words[1], words[2]);
		words[7] = words[6];
		words[6] = words[5];
		words[5] = words[4];
		words[4] = words[3] + tmp1;
		words[3] = words[2];
		words[2] = words[1];
		words[1] = words[0];
		words[0] = tmp1 + tmp2;
	}
}

static void	get_intermediate_hash(t_md5 *s, uint64_t *words)
{
	s->a += words[0];
	s->b += words[1];
	s->c += words[2];
	s->d += words[3];
	s->e += words[4];
	s->f += words[5];
	s->g += words[6];
	s->h += words[7];
}

const void	*sha512_transform(t_md5 *s, const void *data, uint64_t size)
{
	const unsigned char	*ptr = (const unsigned char *)data;
	uint64_t			words[8];
	uint64_t			w[80];

	while (size > 0)
	{
		set_msg_schedule_words(w, ptr);
		words[0] = s->a;
		words[1] = s->b;
		words[2] = s->c;
		words[3] = s->d;
		words[4] = s->e;
		words[5] = s->f;
		words[6] = s->g;
		words[7] = s->h;
		loop(words, w);
		get_intermediate_hash(s, words);

		size -= 128;
		ptr += 128;
	}
	return (ptr);
}
