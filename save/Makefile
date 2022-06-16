########################################
#				PROGRAMS				#
#########################################
NAME = cub3d

#########################################
#				COMMANDS				#
#########################################
CC = clang
MKDIR =	mkdir -p
RM = rm -rf

#########################################
#			DIRECTORIES					#
#########################################
SRCS_DIR = srcs/
OBJ_DIR = objs/
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

#########################################
#			FLAGS COMPILATION			#
#########################################
CFLAGS = -Wall -Werror -Wextra -g
#CFLAGS += -fsanitize=address  -Wno-unused
IFLAGS := -I includes/
LFLAGS := -L$(LIBFT_DIR) -lft
MFLAGS = -ldl -lmlx -L${MLX_DIR} -lm -lXext -lX11 -Imlx $(MLX_PATH)
#########################################
#			FILES PATH					#
#########################################
INC_PATH = includes/cub3d.h
MLX_PATH = ${MLX_DIR}/libmlx.a
#########################################
#			SOURCES	FILES				#
#########################################
SRCS = main.c 									\
	01_Parsing/00_open_file.c 					\
	01_Parsing/01_retrieve_info_in_file.c 		\
	01_Parsing/02_retrieve_map_description.c 	\
	01_Parsing/03_check_info_retrieved.c 		\
	01_Parsing/04_check_map_retrieved.c 		\
	01_Parsing/05_check_map_borders.c 			\
	02_Events_handling/00_handlers.c 			\
	02_Events_handling/01_hooks.c 				\
	02_Events_handling/02_player_moves.c 		\
	03_Graphics/00_init_window.c 				\
	03_Graphics/01_raycasting_init.c 			\
	03_Graphics/02_raycasting_engine.c 			\
	03_Graphics/03_raycasting_utils.c 			\
	03_Graphics/04_2d_map.c 					\
	05_Utils/gnl/get_next_line.c 				\
	05_Utils/gnl/get_next_line_utils.c 			\
	05_Utils/check_arg.c 						\
	05_Utils/free_functions.c 					\
	05_Utils/init_data.c 						\
	05_Utils/utils_functions.c 					\

SRC	= $(addprefix $(SRCS_DIR),$(SRCS))

#########################################
#            OBJECT FILES    	        #
#########################################
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

#########################################
#				COLORS					#
#########################################
RED		:="\033[1;31m"
GREEN	:="\033[1;32m"
PURPLE	:="\033[1;35m"
CYAN	:="\033[1;36m"
EOC		:="\033[0;0m"

#########################################
#				RULES					#
#########################################
all:	${NAME}

${OBJ_DIR}%.o : ${SRCS_DIR}%.c
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $< 

$(NAME): $(OBJS)
	@make -C ${MLX_DIR}
	@make -C $(LIBFT_DIR)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(IFLAGS) -o $(NAME) $(MFLAGS)  
	@echo $(GREEN) "[OK COMPILED]" $(EOC)

clean:
		@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
		@${RM} ${OBJS}
		@${RM} ${OBJ_DIR} 
		@make --no-print-directory -C ${LIBFT_DIR} clean
		@make --no-print-directory -C $(MLX_DIR) clean

fclean: clean
		@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
		@${RM} ${NAME}
		@make --no-print-directory -C $(LIBFT_DIR) fclean
		# @make --no-print-directory -C $(MLX_DIR) fclean

re: 	fclean all

.PHONY: all clean fclean re