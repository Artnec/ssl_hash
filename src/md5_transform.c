/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 16:58:54 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/21 16:58:55 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

#define F(x, y, z)			(z ^ (x & (y ^ z)))
#define G(x, y, z)			(y ^ (z & (x ^ y)))
#define H(x, y, z)			(x ^ y ^ z)
#define I(x, y, z)			(y ^ (x | ~z))

#define GET_U32(n)			(*(uint32_t *)&ptr[n * 4])

#define RTL(a, s)			a = ((a << s) | (a >> (32 - s)))

#define FN(f, a, b, c, d, x, t)		a += f(b, c, d) + x + t

#define STEP(f, a, b, c, d, x, t, s) FN(f, a, b, c, d, x, t); RTL(a, s); a += b

static void		step_f(uint32_t *w, const unsigned char *ptr)
{
	STEP(F, w[0], w[1], w[2], w[3], GET_U32(0), 0xd76aa478, 7);
	STEP(F, w[3], w[0], w[1], w[2], GET_U32(1), 0xe8c7b756, 12);
	STEP(F, w[2], w[3], w[0], w[1], GET_U32(2), 0x242070db, 17);
	STEP(F, w[1], w[2], w[3], w[0], GET_U32(3), 0xc1bdceee, 22);
	STEP(F, w[0], w[1], w[2], w[3], GET_U32(4), 0xf57c0faf, 7);
	STEP(F, w[3], w[0], w[1], w[2], GET_U32(5), 0x4787c62a, 12);
	STEP(F, w[2], w[3], w[0], w[1], GET_U32(6), 0xa8304613, 17);
	STEP(F, w[1], w[2], w[3], w[0], GET_U32(7), 0xfd469501, 22);
	STEP(F, w[0], w[1], w[2], w[3], GET_U32(8), 0x698098d8, 7);
	STEP(F, w[3], w[0], w[1], w[2], GET_U32(9), 0x8b44f7af, 12);
	STEP(F, w[2], w[3], w[0], w[1], GET_U32(10), 0xffff5bb1, 17);
	STEP(F, w[1], w[2], w[3], w[0], GET_U32(11), 0x895cd7be, 22);
	STEP(F, w[0], w[1], w[2], w[3], GET_U32(12), 0x6b901122, 7);
	STEP(F, w[3], w[0], w[1], w[2], GET_U32(13), 0xfd987193, 12);
	STEP(F, w[2], w[3], w[0], w[1], GET_U32(14), 0xa679438e, 17);
	STEP(F, w[1], w[2], w[3], w[0], GET_U32(15), 0x49b40821, 22);
}

static void		step_g(uint32_t *w, const unsigned char *ptr)
{
	STEP(G, w[0], w[1], w[2], w[3], GET_U32(1), 0xf61e2562, 5);
	STEP(G, w[3], w[0], w[1], w[2], GET_U32(6), 0xc040b340, 9);
	STEP(G, w[2], w[3], w[0], w[1], GET_U32(11), 0x265e5a51, 14);
	STEP(G, w[1], w[2], w[3], w[0], GET_U32(0), 0xe9b6c7aa, 20);
	STEP(G, w[0], w[1], w[2], w[3], GET_U32(5), 0xd62f105d, 5);
	STEP(G, w[3], w[0], w[1], w[2], GET_U32(10), 0x02441453, 9);
	STEP(G, w[2], w[3], w[0], w[1], GET_U32(15), 0xd8a1e681, 14);
	STEP(G, w[1], w[2], w[3], w[0], GET_U32(4), 0xe7d3fbc8, 20);
	STEP(G, w[0], w[1], w[2], w[3], GET_U32(9), 0x21e1cde6, 5);
	STEP(G, w[3], w[0], w[1], w[2], GET_U32(14), 0xc33707d6, 9);
	STEP(G, w[2], w[3], w[0], w[1], GET_U32(3), 0xf4d50d87, 14);
	STEP(G, w[1], w[2], w[3], w[0], GET_U32(8), 0x455a14ed, 20);
	STEP(G, w[0], w[1], w[2], w[3], GET_U32(13), 0xa9e3e905, 5);
	STEP(G, w[3], w[0], w[1], w[2], GET_U32(2), 0xfcefa3f8, 9);
	STEP(G, w[2], w[3], w[0], w[1], GET_U32(7), 0x676f02d9, 14);
	STEP(G, w[1], w[2], w[3], w[0], GET_U32(12), 0x8d2a4c8a, 20);
}

static void		step_h(uint32_t *w, const unsigned char *ptr)
{
	STEP(H, w[0], w[1], w[2], w[3], GET_U32(5), 0xfffa3942, 4);
	STEP(H, w[3], w[0], w[1], w[2], GET_U32(8), 0x8771f681, 11);
	STEP(H, w[2], w[3], w[0], w[1], GET_U32(11), 0x6d9d6122, 16);
	STEP(H, w[1], w[2], w[3], w[0], GET_U32(14), 0xfde5380c, 23);
	STEP(H, w[0], w[1], w[2], w[3], GET_U32(1), 0xa4beea44, 4);
	STEP(H, w[3], w[0], w[1], w[2], GET_U32(4), 0x4bdecfa9, 11);
	STEP(H, w[2], w[3], w[0], w[1], GET_U32(7), 0xf6bb4b60, 16);
	STEP(H, w[1], w[2], w[3], w[0], GET_U32(10), 0xbebfbc70, 23);
	STEP(H, w[0], w[1], w[2], w[3], GET_U32(13), 0x289b7ec6, 4);
	STEP(H, w[3], w[0], w[1], w[2], GET_U32(0), 0xeaa127fa, 11);
	STEP(H, w[2], w[3], w[0], w[1], GET_U32(3), 0xd4ef3085, 16);
	STEP(H, w[1], w[2], w[3], w[0], GET_U32(6), 0x04881d05, 23);
	STEP(H, w[0], w[1], w[2], w[3], GET_U32(9), 0xd9d4d039, 4);
	STEP(H, w[3], w[0], w[1], w[2], GET_U32(12), 0xe6db99e5, 11);
	STEP(H, w[2], w[3], w[0], w[1], GET_U32(15), 0x1fa27cf8, 16);
	STEP(H, w[1], w[2], w[3], w[0], GET_U32(2), 0xc4ac5665, 23);
}

static void		step_i(uint32_t *w, const unsigned char *ptr)
{
	STEP(I, w[0], w[1], w[2], w[3], GET_U32(0), 0xf4292244, 6);
	STEP(I, w[3], w[0], w[1], w[2], GET_U32(7), 0x432aff97, 10);
	STEP(I, w[2], w[3], w[0], w[1], GET_U32(14), 0xab9423a7, 15);
	STEP(I, w[1], w[2], w[3], w[0], GET_U32(5), 0xfc93a039, 21);
	STEP(I, w[0], w[1], w[2], w[3], GET_U32(12), 0x655b59c3, 6);
	STEP(I, w[3], w[0], w[1], w[2], GET_U32(3), 0x8f0ccc92, 10);
	STEP(I, w[2], w[3], w[0], w[1], GET_U32(10), 0xffeff47d, 15);
	STEP(I, w[1], w[2], w[3], w[0], GET_U32(1), 0x85845dd1, 21);
	STEP(I, w[0], w[1], w[2], w[3], GET_U32(8), 0x6fa87e4f, 6);
	STEP(I, w[3], w[0], w[1], w[2], GET_U32(15), 0xfe2ce6e0, 10);
	STEP(I, w[2], w[3], w[0], w[1], GET_U32(6), 0xa3014314, 15);
	STEP(I, w[1], w[2], w[3], w[0], GET_U32(13), 0x4e0811a1, 21);
	STEP(I, w[0], w[1], w[2], w[3], GET_U32(4), 0xf7537e82, 6);
	STEP(I, w[3], w[0], w[1], w[2], GET_U32(11), 0xbd3af235, 10);
	STEP(I, w[2], w[3], w[0], w[1], GET_U32(2), 0x2ad7d2bb, 15);
	STEP(I, w[1], w[2], w[3], w[0], GET_U32(9), 0xeb86d391, 21);
}

const void		*md5_transform(t_md5 *s, const void *data, uint64_t size)
{
	const unsigned char	*ptr = (const unsigned char *)data;
	uint32_t			words[4];

	while (size > 0)
	{
		words[0] = s->a;
		words[1] = s->b;
		words[2] = s->c;
		words[3] = s->d;
		step_f(words, ptr);
		step_g(words, ptr);
		step_h(words, ptr);
		step_i(words, ptr);
		s->a += words[0];
		s->b += words[1];
		s->c += words[2];
		s->d += words[3];

		ptr += 64;
		size -= 64;
	}
	return (ptr);
}
