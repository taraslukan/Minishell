# Nome dell'eseguibile
NAME = minishell

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I/usr/local/opt/readline/include -I$(LIBFTDIR)/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline -L$(LIBFTDIR) -lft
LIBFTDIR = ./libft

# Colori
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[1;31m
NC = \033[0m  # Reset

SRCS = main.c \
     $(wildcard ./new_read/*.c) \
     $(wildcard ./signal/*.c) \
     $(wildcard ./builtIn/*.c) \
     $(wildcard ./utils/*.c) \
     $(wildcard ./env/*.c) \
     $(wildcard ./exv/*.c) \
     $(wildcard ./token/*.c)
OBJS = $(SRCS:%.c=%.o)

all: banner $(NAME)

banner:
	@echo "${BLUE}============================${NC}"
	@echo "${YELLOW} Compilazione di Minishell... ${NC}"
	@echo "${BLUE}============================${NC}"

$(NAME): $(OBJS) $(LIBFTDIR)/libft.a
	@echo "${GREEN}[✔] Creazione eseguibile: ${NAME}${NC}"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "${GREEN}[✔] Minishell compilato con successo!${NC}"
	@$(MAKE) ask_exec

$(LIBFTDIR)/libft.a:
	@echo "${YELLOW}[→] Compilazione della libreria libft...${NC}"
	@make -C $(LIBFTDIR)
	@echo "${GREEN}[✔] libft compilata!${NC}"

%.o: %.c
	@echo "${YELLOW}[→] Compilazione: $<${NC}"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "${RED}[✖] Pulizia degli oggetti...${NC}"
	@rm -rf $(OBJS)
	@make -C $(LIBFTDIR) clean
	@echo "${GREEN}[✔] Pulizia completata!${NC}"

fclean: clean
	@echo "${RED}[✖] Rimozione dell'eseguibile...${NC}"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean
	@echo "${GREEN}[✔] Pulizia completa!${NC}"

re: fclean all

ask_exec:
	@echo "${BLUE}=================================${NC}"
	@echo "${GREEN}Minishell pronto all'esecuzione!${NC}"
	@echo "${BLUE}=================================${NC}"
	@printf "${YELLOW}Vuoi avviare Minishell? (y/n): ${NC}"
	@read choice; if [ "$$choice" = "y" ]; then ./minishell; fi

exec: re

.PHONY: all clean fclean re exec ask_exec
