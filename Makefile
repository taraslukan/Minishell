# Nome dell'eseguibile
NAME = minishell

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

# File sorgenti e oggetti
SRCS = main.c \
       Read/read.c
OBJS = $(SRCS:src/%.c=obj/%.o)

# Regola principale
all: $(NAME)

# Regola per creare l'eseguibile
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

# Regola per creare i file oggetto
obj/%.o: src/%.c | obj
	mkdir -p $(dir $@) # Crea la directory per i file oggetto
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per creare la directory dei file oggetto
obj:
	mkdir -p obj

# Pulizia dei file oggetto
clean:
	rm -rf obj

# Pulizia completa (incluso l'eseguibile)
fclean: clean
	rm -f $(NAME)

# Ricompilazione completa
re: fclean all

# Dichiarazione delle regole "phony"
.PHONY: all clean fclean re
