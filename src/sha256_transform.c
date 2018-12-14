/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 20:20:09 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/22 20:20:10 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

#define ROTR(x, n)		((x >> n) | (x << (32 - n)))
#define SHR(x, n)		(x >> n)

#define E0(x)			(ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define E1(x)			(ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define O0(x)			(ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define O1(x)			(ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))
#define CH(x, y, z)		((x & y) ^ (~x & z))
#define MAJ(x, y, z)	((x & y) ^ (x & z) ^ (y & z))

extern const uint32_t g_k256[64];

static void	set_msg_schedule_words(uint32_t *w, const unsigned char *ptr)
{
	int i = 0;
	while (i < 16)
	{
		w[i] = ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
		ptr += 4;
		i++;
	}
	while (i < 64)
	{
		w[i] = O1(w[i - 2]) + w[i - 7] + O0(w[i - 15]) + w[i - 16];
		i++;
	}
}

static void	loop(uint32_t *words, uint32_t *w)
{
	for (int n = 0; n < 64; n++)
	{
		uint32_t tmp1 = words[7] + E1(words[4]) +
		CH(words[4], words[5], words[6]) + g_k256[n] + w[n];
		uint32_t tmp2 = E0(words[0]) + MAJ(words[0], words[1], words[2]);
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

static void	get_intermediate_hash(t_md5 *s, uint32_t *words)
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

const void	*sha256_transform(t_md5 *s, const void *data, uint64_t size)
{
	const unsigned char	*ptr = (const unsigned char *)data;
	uint32_t			words[8];
	uint32_t			w[64];

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

		size -= 64;
		ptr += 64;
	}
	return (ptr);
}
