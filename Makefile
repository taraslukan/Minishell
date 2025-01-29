# Nome dell'eseguibile
NAME = minishell

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I/usr/local/opt/readline/include -I$(LIBFTDIR)/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline -L$(LIBFTDIR) -lft
LIBFTDIR = ./libft

SRCS = main.c \
		$(wildcard ./signal/*.c) \
		$(wildcard ./builtIn/*.c) \
		$(wildcard ./utils/*.c) \
		$(wildcard ./env/*.c) \
		$(wildcard ./exv/*.c) \
    	$(wildcard ./read/*.c) \
    	$(wildcard ./token/*.c)
OBJS = $(SRCS:%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTDIR)/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(LIBFTDIR)/libft.a:
	make -C $(LIBFTDIR)

obj/%.o: %.c | obj
	mkdir -p $(dir $@) # Crea la directory per i file oggetto
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

exec: re
	./minishell

.PHONY: all clean fclean re