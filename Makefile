# Nome dell'eseguibile
NAME = minishell

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -I/usr/local/opt/readline/include -I$(LIBFTDIR)/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline -lhistory -L$(LIBFTDIR) -lft
LIBFTDIR = ./libft

# Colori
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[1;31m
NC = \033[0m  # Reset

# File sorgenti
SRCS = main.c \
     $(wildcard ./new_read/*.c) \
     $(wildcard ./signal/*.c) \
     $(wildcard ./builtIn/*.c) \
     $(wildcard ./utils/*.c) \
     $(wildcard ./env/*.c) \
     $(wildcard ./exv/*.c) \
     $(wildcard ./token/*.c)
OBJS = $(SRCS:%.c=%.o)

all: banner $(NAME) clean_objs

banner:
	@echo "${BLUE}============================${NC}"
	@echo "${YELLOW} Compilazione di Minishell... ${NC}"
	@echo "${BLUE}============================${NC}"

$(NAME): $(OBJS) $(LIBFTDIR)/libft.a
	@echo "${GREEN}[✔] Creazione eseguibile: ${NAME}${NC}"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "${GREEN}[✔] Minishell compilato con successo!${NC}"

$(LIBFTDIR)/libft.a:
	@echo "${YELLOW}[→] Compilazione della libreria libft...${NC}"
	@make -C $(LIBFTDIR)
	@echo "${GREEN}[✔] libft compilata!${NC}"

%.o: %.c
	@echo "${YELLOW}[→] Compilazione: $<${NC}"
	@$(CC) $(CFLAGS) -c $< -o $@

clean_objs:
	@rm -rf $(OBJS)
	@echo "${GREEN}[✔] Pulizia completata!${NC}"

clean:
	@echo "${RED}[✖] Pulizia degli oggetti e file temporanei...${NC}"
	@rm -rf $(OBJS)
	@make -C $(LIBFTDIR) clean
	@echo "${GREEN}[✔] Pulizia completata!${NC}"

fclean: clean
	@echo "${RED}[✖] Rimozione dell'eseguibile...${NC}"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean
	@echo "${GREEN}[✔] Pulizia completa!${NC}"

re: fclean all

.PHONY: all clean fclean re clean_objs
