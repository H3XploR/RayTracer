NAME = miniRT

MINILIBX = minilibx-linux/libmlx.a
LIBFT = libft/libft.a

SRC = $(wildcard *.c)
DIR_OBJ = obj
OBJ = $(addprefix $(DIR_OBJ)/, $(notdir $(SRC:.c=.o)))

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
INCLUDES = -I. -Ilibft -Iminilibx-linux
LDFLAGS = -Llibft -Lminilibx-linux
LDLIBS = -lft -lmlx -lXext -lX11 -lm -lbsd

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

$(DIR_OBJ)/%.o: %.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

$(LIBFT):
	@make -C libft all

$(MINILIBX):
	@make -C minilibx-linux

all: $(NAME)

clean:
	@make -C libft clean
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@make -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re

