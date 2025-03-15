##
## EPITECH PROJECT, 2024
## Makefile lib
## File description:
## MakeFile dans le fichier lib
##

# Couleurs
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[1;37m
NC=\033[0m # No Color

NAME = libmy.a

LIB =	./my_compute_power_rec.c\
	./my_getnbr.c\
	./my_isneg.c\
	./my_put_nbr.c\
	./my_putchar.c\
	./my_putstr.c\
	./my_strdup.c\
	./my_strncmp.c\
	./my_strcpy.c\
	./my_strlen.c\
	./my_strncpy.c\
	./my_swap.c\
	./my_sort_params.c\
	./my_revstr.c\
	./my_str_to_word_array.c\
	./flag_c.c\
	./flag_d.c\
	./flag_i.c\
	./flag_o.c\
	./flag_percent.c\
	./flag_s.c\
	./flag_x.c\
	./flag_x2.c\
	./my_printf.c\
	./my_strcmp.c\
	./my_strnmajcmp.c\
	./my_strcat.c\
	./my_show_word_in_array.c\
	./my_getenv.c\
	./extract_str.c\
	./extract_str_advanced.c\
	./my_strchr.c\
	./my_strtok.c\
	./my_str_to_word_array_advanced.c\
	./my_str_tolower.c\
	./my_free_word_array.c\
	./my_atoi.c\
	./my_isalpha.c\
	./my_strncat.c\
	./my_isdigit.c\
	./my_str_isalnum.c\
	./free_array.c\
	./my_compute_square_root.c\
	./my_strmajcmp.c\
	./my_str_isnum.c\
	./my_copy_word_in_array.c

OBJ_LIB  	=	 $(LIB:.c=.o)

CFLAGS += -g -Wall -Werror -Wextra -W -Iinclude

all: 	$(NAME)

$(NAME): $(OBJ_LIB)
	@echo "$(YELLOW)Building Lib$(NAME)...$(NC)"
	@ar rcs $(NAME) $(OBJ_LIB)
	@mv $(NAME) ../../
	@echo "$(GREEN)Build complete!$(NC)"

$(OBJ_LIB): %.o: %.c
	@echo "$(YELLOW)Compiling $<...$(NC)"  # Affiche la ligne de compilation
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "\033[0;31mBUILD FAILED!$(NC)"; \
		exit 1; \
	}

clean:
	@echo "$(RED)Cleaning up object files...$(NC)"
	@rm -f $(OBJ_LIB)
	@echo "$(MAGENTA)Object files cleaned!$(NC)"

fclean: clean
	@echo "$(RED)Cleaning up library...$(NC)"
	@rm -f $(NAME)
	@echo "$(CYAN)Library cleaned!$(NC)"

re:
	@echo "$(BLUE)Rebuilding everything...$(NC)"
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "$(WHITE)Rebuild complete!$(NC)"
