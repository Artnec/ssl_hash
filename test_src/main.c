#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

int		check_args(int argc, char **argv)
{
	if (argc != 4)
	{
		printf("usage: %s [md5 | sha224|256|384|512|512/224|512/256", argv[0]);
		printf(" | whirlpool] start_len end_len\n");
		return (1);
	}
	if (strcmp(argv[1], "md5") && strcmp(argv[1], "sha224") &&
		strcmp(argv[1], "sha256") && strcmp(argv[1], "sha384") &&
		strcmp(argv[1], "sha512") && strcmp(argv[1], "sha512/224") &&
		strcmp(argv[1], "sha512/256") && strcmp(argv[1], "whirlpool"))
	{
		printf("chose md5 | sha224|256|384|512|512/224|512/256");
		printf(" | whirlpool as first argument\n");
		return (1);
	}
	return (0);
}

int		compare_outputs(char *algo, int n, FILE *f1, FILE *f2)
{
	char	output1[256];
	char	output2[256];

	int bytes_read1 = fread(output1, 1, 256, f1);
	int bytes_read2 = fread(output2, 1, 256, f2);
	output1[bytes_read1] = '\0';
	output2[bytes_read2] = '\0';
	pclose(f1);
	pclose(f2);
	if (strcmp(output1, output2))
	{
		printf("%d\n%s%s", n, output1, output2);
		return (1);
	}
	printf("%s %d OK\n", algo, n);
	return (0);
}

int		get_and_compare_outputs(char *algo, int n)
{
	FILE	*f1;
	FILE	*f2;
	char	comm1[64];
	char	comm2[64];

	if (!strcmp(algo, "sha512/256"))
	{
		f1 = popen("shasum -a 512256 test_file", "r");
		f2 = popen("./ssl_hash sha512/256 -r test_file", "r");
	}
	else if (!strcmp(algo, "sha512/224"))
	{
		f1 = popen("shasum -a 512224 test_file", "r");
		f2 = popen("./ssl_hash sha512/224 -r test_file", "r");
	}
	else
	{
		sprintf(comm1, "openssl %s < test_file", algo);
		sprintf(comm2, "./ssl_hash %s -q test_file", algo);
		f1 = popen(comm1, "r");
		f2 = popen(comm2, "r");
	}
	return (compare_outputs(algo, n, f1, f2));
}

void	test_loop(int start_file_len, int end_file_len, char *algo)
{
	for (int n = 0; n <= end_file_len - start_file_len; n++)
	{
		int fd = open("test_file", O_TRUNC | O_CREAT | O_WRONLY, 0600);
		for (int i = 0; i < start_file_len + n; i++)
		{
			char c = rand();
			write(fd, &c, 1);
		}
		close(fd);
		if (get_and_compare_outputs(algo, n + start_file_len))
			return ;
	}
}

int		main(int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	int start_file_len = atoi(argv[2]);
	if (start_file_len < 1 || start_file_len > 1000000)
	{
		printf("error: wrong start file lenght\n");
		return (1);
	}
	int end_file_len = atoi(argv[3]);
	if (end_file_len < start_file_len || end_file_len > start_file_len + 200000)
	{
		printf("error: wrong end file lenght\n");
		return (1);
	}
	srand(time(0));
	test_loop(start_file_len, end_file_len, argv[1]);
	system("rm -f test_file");
	return (0);
}
