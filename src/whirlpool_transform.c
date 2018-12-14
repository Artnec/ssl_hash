/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:11:24 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/25 17:11:25 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_hash.h"

#define GET_U64(n)			(*(uint64_t *)&ptr[n * 8])

#define WS					g_whirlpool_sbox
#define S1(src, shift)		(WS[0][(int)(src[shift & 7] >> 56)])
#define S2(src, shift)		(WS[1][(int)(src[(shift + 7) & 7] >> 48) & 0xff])
#define S3(src, shift)		(WS[2][(int)(src[(shift + 6) & 7] >> 40) & 0xff])
#define S4(src, shift)		(WS[3][(int)(src[(shift + 5) & 7] >> 32) & 0xff])
#define S5(src, shift)		(WS[4][(int)(src[(shift + 4) & 7] >> 24) & 0xff])
#define S6(src, shift)		(WS[5][(int)(src[(shift + 3) & 7] >> 16) & 0xff])
#define S7(src, shift)		(WS[6][(int)(src[(shift + 2) & 7] >> 8) & 0xff])
#define S8(src, shift)		(WS[7][(int)(src[(shift + 1) & 7]) & 0xff])

#define S123(src, shift)	(S1(src, shift) ^ S2(src, shift) ^ S3(src, shift))
#define S12345(src, shift)	(S123(src, shift) ^ S4(src, shift) ^ S5(src, shift))
#define S678(src, shift)	(S6(src, shift) ^ S7(src, shift) ^ S8(src, shift))
#define STEP(src, shift)	(S12345(src, shift) ^ S678(src, shift))

extern const uint64_t	g_whirlpool_sbox[8][256];
extern const uint64_t	g_rc[10];

uint64_t		u64_reverse_endian(uint64_t x)
{
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
	return (x);
}

static void		loop(uint64_t k[2][8], uint64_t state[2][8])
{
	int m = 0;
	int i = 0;
	while (i < 10)
	{
		k[m ^ 1][0] = STEP(k[m], 0) ^ g_rc[i++];
		k[m ^ 1][1] = STEP(k[m], 1);
		k[m ^ 1][2] = STEP(k[m], 2);
		k[m ^ 1][3] = STEP(k[m], 3);
		k[m ^ 1][4] = STEP(k[m], 4);
		k[m ^ 1][5] = STEP(k[m], 5);
		k[m ^ 1][6] = STEP(k[m], 6);
		k[m ^ 1][7] = STEP(k[m], 7);
		state[m ^ 1][0] = STEP(state[m], 0) ^ k[m ^ 1][0];
		state[m ^ 1][1] = STEP(state[m], 1) ^ k[m ^ 1][1];
		state[m ^ 1][2] = STEP(state[m], 2) ^ k[m ^ 1][2];
		state[m ^ 1][3] = STEP(state[m], 3) ^ k[m ^ 1][3];
		state[m ^ 1][4] = STEP(state[m], 4) ^ k[m ^ 1][4];
		state[m ^ 1][5] = STEP(state[m], 5) ^ k[m ^ 1][5];
		state[m ^ 1][6] = STEP(state[m], 6) ^ k[m ^ 1][6];
		state[m ^ 1][7] = STEP(state[m], 7) ^ k[m ^ 1][7];
		m = m ^ 1;
	}
}

static void		calc_hash(uint64_t *hash, uint64_t state[2][8])
{
	hash[0] ^= state[0][0];
	hash[1] ^= state[0][1];
	hash[2] ^= state[0][2];
	hash[3] ^= state[0][3];
	hash[4] ^= state[0][4];
	hash[5] ^= state[0][5];
	hash[6] ^= state[0][6];
	hash[7] ^= state[0][7];
}

const void		*whirlpool_transform(uint64_t *hash,
									const void *data, uint64_t size)
{
	const unsigned char	*ptr = (const unsigned char *)data;
	uint64_t			k[2][8];
	uint64_t			state[2][8];

	while (size > 0)
	{
		int i = 0;
		while (i < 8)
		{
			k[0][i] = hash[i];
			state[0][i] = u64_reverse_endian(GET_U64(i)) ^ hash[i];
			hash[i] = state[0][i];
			i++;
		}
		loop(k, state);
		calc_hash(hash, state);

		size -= 64;
		ptr += 64;
	}
	return (ptr);
}
