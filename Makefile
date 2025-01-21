# Nome dell'eseguibile
NAME = minishell

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I/usr/local/opt/readline/include -I$(LIBFTDIR)/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline -L$(LIBFTDIR) -lft
LIBFTDIR = ./libft

# File sorgenti e oggetti
SRCS = main.c \
		$(wildcard ./signal/*.c) \
		$(wildcard ./builtIn/*.c) \
		$(wildcard ./utils/*.c) \
		$(wildcard ./env/*.c) \
		$(wildcard ./exv/*.c) \
    	$(wildcard ./read/*.c) \
    	$(wildcard ./token/*.c)
OBJS = $(SRCS:%.c=obj/%.o)

# Regola principale
all: $(NAME)

# Regola per creare l'eseguibile
$(NAME): $(OBJS) $(LIBFTDIR)/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

# Regola per compilare libft
$(LIBFTDIR)/libft.a:
	make -C $(LIBFTDIR)

# Regola per creare i file oggetto
obj/%.o: %.c | obj
	mkdir -p $(dir $@) # Crea la directory per i file oggetto
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per creare la directory dei file oggetto
obj:
	mkdir -p obj

# Pulizia dei file oggetto
clean:
	rm -rf obj
	make -C $(LIBFTDIR) clean

# Pulizia completa (incluso l'eseguibile e la libft)
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

# Ricompilazione completa
re: fclean all

# Dichiarazione delle regole "phony"
.PHONY: all clean fclean re