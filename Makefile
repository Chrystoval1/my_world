##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## automation if compilation/commands
##

GREEN		=	\033[0;32m
RED		=	\033[0;31m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
MAGENTA		=	\033[0;35m
CYAN		=	\033[0;36m
WHITE		=	\033[0;37m
BOLD		=	\033[1m
RESET		=	\033[0m

NAME		=	my_world
VERSION		=	1.0.0

CC		=	gcc
FLAGS		=	-l csfml-graphics -l csfml-window -l csfml-system \
			-l csfml-audio -lm -Wall -Wextra -g -Iinclude
CFLAGS		+=	$(FLAGS)

SRC 		=	src/main.c \
			src/map.c \
			src/rotate_map.c \
			src/draw_map.c \
			src/ui.c \
			src/draw_ui.c \
			src/ui_interaction.c \
			src/draw_borders.c \
			src/map_interaction.c \
			src/help_messages.c \
			src/save.c \
			src/free.c

OBJ		=	$(SRC:.c=.o)

TOTAL_FILES	=	$(words $(SRC))
COMPILED_FILES	=	0
PROGRESS	=	0

all:		project_logo $(NAME)
		@echo "$(GREEN)$(BOLD)✓ Build complete for $(NAME) v$(VERSION)$(RESET)"
		@echo "$(CYAN)→ Run './$(NAME)' to start the program$(RESET)"

project_logo:
	@echo "$(BLUE)╔═══════════════════════╗$(RESET)"
	@echo "$(BLUE)║        $(YELLOW)MyWorld$(BLUE)        ║$(RESET)"
	@echo "$(BLUE)╚═══════════════════════╝$(RESET)"
	@echo ""

$(NAME):	$(OBJ)
	@echo "$(YELLOW)⚡ Linking objects into executable...$(RESET)"
	@$(CC) -o $(NAME) $(SRC) $(FLAGS)
	@echo "$(GREEN)✓ Successfully created$(BOLD) $(NAME)$(RESET)"

%.o:		%.c
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
	@$(eval PROGRESS=$(shell echo $$(($(COMPILED_FILES)*100/$(TOTAL_FILES)))))
	@printf "$(YELLOW)⚡ [%3d%%] Compiling: $(WHITE)%s$(RESET)\n" $(PROGRESS) $<
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)⚡ Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)✓ Object files cleaned$(RESET)"

fclean:		clean
	@echo "$(YELLOW)⚡ Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Project fully cleaned$(RESET)"

re:		project_logo fclean all

help:
	@echo "$(BLUE)$(BOLD)Available commands:$(RESET)"
	@echo "$(CYAN)make$(RESET)        - Build the project"
	@echo "$(CYAN)make clean$(RESET)  - Remove object files"
	@echo "$(CYAN)make fclean$(RESET) - Remove object files and executable"
	@echo "$(CYAN)make re$(RESET)     - Rebuild the entire project"
	@echo "$(CYAN)make help$(RESET)   - Display this help message"

.PHONY: all clean fclean re help project_logo
