# Verif HOSTTYPE ENV

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#Variables

NAME		= libft_malloc_$(HOSTTYPE).so
INCLUDE		= includes
LIBFT		= libft
SRC_DIR		= srcs/
OBJ_DIR		= obj/
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I
DEBUGFLAGS	= -g3 -O0
RM			= rm -f
AR			= ar rcs

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

SRC_FILES	= ft_malloc ft_malloc_utils ft_malloc_alloc ft_malloc_free

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

debug:		$(LIBFT)/libft.a
			@$(CC) $(DEBUGFLAGS) -I$(INCLUDE) -I$(LIBFT)/include $(SRC) $(LIBFT)/libft.a -o a.out
			@echo "$(GREEN)debug executable compiled!$(DEF_COLOR)"

$(LIBFT)/libft.a:
			@$(MAKE) -C $(LIBFT)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@if [ ! -e libft_malloc.so ]; then ln -s $(NAME) libft_malloc.so; fi
			@$(AR) $(NAME) $(OBJ)
			@echo "$(GREEN)malloc compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIBFT)
			@echo "$(BLUE)malloc object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)/libft.a
			@$(RM) libft_malloc.so
			@$(RM) a.out
			@echo "$(CYAN)malloc executable files cleaned!$(DEF_COLOR)"
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for malloc!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) $(LIBFT) | grep -v Norme -B1 || true

.PHONY:		all debug clean fclean re norm