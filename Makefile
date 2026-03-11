NAME = philo

SOURCES = src/philo.c \
			src/utils.c\
			src/parsing/parsing.c \
			src/thread/thread.c \
			src/thread/eating.c \
			src/thread/sleeping.c \
			src/thread/thinking.c

OBJS_DIR = objs
OBJECTS = $(SOURCES:src/%.c=$(OBJS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iheaders
RM = rm -rf

GREEN = \033[1;32m
RED = \033[1;31m
RESET = \033[0m

all: $(NAME)
$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c philo.h
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN)✔ Compilation terminée$(RESET)\n"


clean:
	@$(RM) $(OBJS_DIR)
	@printf "$(RED)✖ Fichiers objets supprimés.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)✖ Fichiers objets supprimés.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re