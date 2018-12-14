NAME			=	ssl_hash

TEST_NAME		=	test

CC				=	clang

FLAGS			=	-O3 -Wall -Werror -Wextra -Wshadow

SRC				=	main.c		read_commands_from_stdin.c		read_input.c \
					parse_args.c	read_string_file_stdin.c 	get_result_string.c \
					sha256.c	sha512.c	sha256_final.c		sha512_final.c \
					md5_whirlpool.c		md5_whirlpool_final.c	update.c \
					md5_transform.c		sha256_transform.c	sha512_transform.c \
					whirlpool_transform.c	whirlpool_sbox.c	sha256_sbox.c \
					sha512_sbox.c

TEST_SRC		=	main.c

INC				=	ssl_hash.h

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
TEST_OBJ		=	$(addprefix $(TEST_SRC_DIR), $(TEST_SRC:.c=.o))
HEADER			=	$(addprefix $(SRC_DIR), $(INC))

SRC_DIR			=	src/
TEST_SRC_DIR	=	test_src/
OBJ_DIR			=	obj/


all: $(NAME) $(TEST_NAME)


static_analysis:
	cppcheck -q --enable=all --inconclusive $(SRC_DIR) $(TEST_SRC_DIR)


obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | obj
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)



$(TEST_SRC_DIR)%.o: $(TEST_SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@

$(TEST_NAME): $(TEST_OBJ)
	$(CC) $(FLAGS) $(TEST_OBJ) -o $(TEST_NAME)



clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all
