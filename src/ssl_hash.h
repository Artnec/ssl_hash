#ifndef SSL_HASH_H
# define SSL_HASH_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define BUFF_SIZE	524288


typedef struct		s_ssl
{
	int				r_flag;
	int				q_flag;
	int				in_flag;
	char			*commands[8];
	char			*(*fun[8])(char *input, uint64_t size);
	int				commands_num;
	int				com;
}					t_ssl;

typedef struct		s_md5
{
	uint64_t		low;
	uint64_t		high;
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
	uint64_t		hash[8];
	unsigned char	buffer[128];
}					t_md5;


void				read_commands_from_stdin(t_ssl *s);
void				parse_args(char **argv, t_ssl *s);
char				*read_input(int fd, uint64_t *size);
void				read_file(char *alg, char *file_name, t_ssl *s);
void				read_stdin(t_ssl *s);
void				read_string(char *str, char *alg, t_ssl *s);
char				*get_result_string(unsigned char *result, int size);
void				u32_to_chars_reverse_endian(unsigned char *str, uint32_t n);
void				u64_to_chars_reverse_endian(unsigned char *str, uint64_t n);

char				*md5(char *input, uint64_t size);
const void			*md5_transform(t_md5 *s, const void *data, uint64_t size);
void				md5_update(t_md5 *s, const void *data, uint64_t size);
void				md5_final(unsigned char *result, t_md5 *s);

char				*sha256(char *input, uint64_t size);
const void			*sha256_transform(t_md5 *s, const void *data,
									uint64_t size);
void				sha256_update(t_md5 *s, const void *data, uint64_t size);
void				sha256_final(unsigned char *result, t_md5 *s);
char				*sha224(char *input, uint64_t size);
void				sha224_final(unsigned char *result, t_md5 *s);

char				*sha512(char *input, uint64_t size);
const void			*sha512_transform(t_md5 *s, const void *data,
									uint64_t size);
void				sha512_update(t_md5 *s, const void *data, uint64_t size);
void				sha512_final(unsigned char *result, t_md5 *s);
char				*sha384(char *input, uint64_t size);
void				sha384_final(unsigned char *result, t_md5 *s);
char				*sha512_256(char *input, uint64_t size);
void				sha512_256_final(unsigned char *result, t_md5 *s);
char				*sha512_224(char *input, uint64_t size);
void				sha512_224_final(unsigned char *result, t_md5 *s);

char				*whirlpool(char *input, uint64_t size);
const void			*whirlpool_transform(uint64_t *hash, const void *data,
										uint64_t size);
void				whirlpool_update(t_md5 *s, const void *data, uint64_t size);
void				whirlpool_final(unsigned char *result, t_md5 *s);

#endif