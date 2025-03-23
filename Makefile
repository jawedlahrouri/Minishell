##
## EPITECH PROJECT, 2025
## B-CPE-200-LIL-2-1-robotfactory-lucas.lhomme
## File description:
## Makefile
##
# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
NC=\033[0m # No Color

# Variables
NAME = mysh
CFLAGS = -Iinclude -Ilib/my/include -fdiagnostics-color=always
FLAGS = -g -Wall -Wextra -W
SRC =	./src/main.c \
		./src/my_cd.c \
		./src/command.c\
		./src/path.c\
		./src/setenv.c\
		./src/delete_list.c \
		./src/builtin.c\
		./src/pipe.c\
		./src/redirections.c

OBJ = $(SRC:.c=.o)
LIBMY = libmy.a

# Default target
all: $(LIBMY) $(NAME)

# Compilation de l'exécutable principal
$(NAME): $(OBJ)
	@echo "$(YELLOW)Building $@...$(NC)"
	@OUTPUT=$$(gcc $(FLAGS) $(CFLAGS) -o $@ $^ $(LIBMY) 2>&1); \
	ERRORS=$$(echo "$$OUTPUT" | grep -c "error:"); \
	WARNINGS=$$(echo "$$OUTPUT" | grep -c "warning:"); \
	echo "$$OUTPUT"; \
	if [ $$ERRORS -eq 0 ]; then \
		echo "$(GREEN)Build complete!\
		$(MAGENTA)warnings :$$WARNINGS, $(RED)errors: $$ERRORS"; \
	else \
		echo "$(RED)Build failed with $$ERRORS errors\
		$(MAGENTA) and $$WARNINGS warnings!$(NC)"; \
	fi

# Compilation of object files
%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@ || { \
		echo "$(RED)BUILD FAILED!$(NC)"; \
		exit 1; \
	}

# Compilation of the library
$(LIBMY):
	@echo "$(BLUE)Building library...$(NC)"
	@$(MAKE) --no-print-directory -C lib/my all

# Clean up object files and executables
clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@$(MAKE) --no-print-directory -C lib/my/ clean
	@rm -f $(OBJ)

# Full clean up
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBMY)

# Rebuild everything
re: fclean all

# Debug mode
debug: CFLAGS += -g
debug: $(NAME)

# Rebuild in debug mode
redebug: fclean debug

# Phony targets
.PHONY: all clean fclean re debug redebug
