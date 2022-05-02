NAME		=	miniRT

MAIN_DIR	=	src/main/
MAIN_FILE	=	main.c \
				init.c \
				minirt.c

PARSER_DIR	=	src/parser/
PARSER_FILE	=	parser.c \
				parser_utils.c

RENDER_DIR	=	src/render/
RENDER_FILE	=	render.c \
				render_utils.c \
				lighting.c

DRAW_DIR	=	src/draw/
DRAW_FILE	=	draw_utils.c \
				vector_utils.c \
				intersect.c

OBJECT_DIR	=	src/objects/
OBJECT_FILE	=	shapes.c \
				lights.c

DEBUG_DIR	=	src/test_debug/
DEBUG_FILE	=	rt_debug.c

SRC_DIRS	=	$(MAIN_DIR) $(PARSER_DIR) $(RENDER_DIR) $(DRAW_DIR) $(OBJECT_DIR) $(DEBUG_DIR)
SRC			=	$(MAIN_FILE) $(PARSER_FILE) $(RENDER_FILE) $(DRAW_FILE) $(OBJECT_FILE) $(DEBUG_FILE)

OBJ_DIR		=	obj/
OBJ 		=	$(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

INCL_DIRS	=	$(addsuffix 'include', $(SRC_DIRS)) MLX42/include/MLX42/
INCLUDES	=	-Ilibft $(addprefix -I, $(INCL_DIRS))

#LIB			=	-Llibft -lft -L/opt/homebrew/Cellar/glfw/3.3.6/lib/ -lglfw -LMLX42 -lmlx42
 LIB			=	-Llibft -lft -L/opt/homebrew/opt/glfw/lib/ -lglfw -LMLX42 -lmlx42

CFLAGS		=	-Wall -Werror -Wextra -O3 #-g -fsanitize=address

CC			=	gcc

vpath %.c $(SRC_DIRS)

$(info )

all: $(NAME)

bonus: all

test:
	@echo
	@echo SRC = $(SRC)
	@echo
	@echo SRC_DIRS = $(SRC_DIRS)
	@echo
	@echo OBJ = $(OBJ)
	@echo
	@echo INCL_DIRS = $(INCL_DIRS)
	@echo
	@echo INCLUDES = $(INCLUDES)
	@echo

$(NAME): $(OBJ)
	@echo
	@echo "\033[35mBuilding libft\033[0m"
	@make -C libft
	@echo
	@echo "\033[35mBuilding MLX42\033[0m"
	@make -C MLX42
	@echo
	@echo "\033[36mLinking binary file:     $@ 📺 💫\033[0m"
	@echo
	@$(CC) $^ $(LIB) $(CFLAGS) -o $@

$(OBJ_DIR)%.o:%.c
	@mkdir -p $(@D)
	@echo "\033[34mCompiling object file:   $@\033[0m"
	@$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

libft:
	@make bonus -C libft

clean:
	@echo "\033[31mRemoving object files\033[0m"
	@echo
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "\033[31mRemoving binary\033[0m"
	@echo
	@rm -f $(NAME)
	@make fclean -C libft

re: clean all

reall: fclean all

rerun: re
	./miniRT

.PHONY:	all libft norme clean fclean re reall
