NAME     =	Cub3D

# 	Compiler  #
CC       =	gcc

#	Flags     #
CFLAGS   =	-Wall -Wextra -Werror -O3#-g3 -fsanitize=address -O3
GFLAGS   =	-lm -L$(MLX_PATH) -lmlx -I$(MLX_PATH) -framework OpenGL -framework Appkit

# 	Headers   #
HEADER_P = 	./includes
HEADER_N =	cub3d.h
HEADER   =	$(addprefix $(HEADER_P)/,$(HEADER_N))

#	Sources   #
SRC_PATH =	./srcs
SRC_NAME =	main.c \
			display.c \
			init.c \
			map.c \
			moves1.c \
			moves2.c \
			raycasting.c \
			load.c \
			load2.c \
			image.c \
			objects.c \
			objects2.c \
			screenshot.c \
			get_next_line.c \
			parse.c \
			ft_atoi.c \
			get_next_line_utils.c \
			parse2.c \
			parse3.c \
			parse4.c \
			norme.c
SRC      =	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

DEP  = $(OBJ:%.o=%.d)

#	Objects   #
OBJ_PATH =	./.objs
OBJ_NAME =	$(SRC_NAME:.c=.o)
OBJ      =	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

#	MiniLibX  #
MLX_PATH =	./mlx
MLX_LIB  =	libCub3d.a
MLX      =	$(addprefix $(MLX_PATH)/,$(MLX_LIB))

################################################################################

all : $(MLX_LIB) $(NAME)

$(MLX_LIB) :
	@make -C $(MLX_PATH)
	
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(GFLAGS) 

-include $(DEP)
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -MMD -I$(HEADER_P) -o $@ -c $<

clean :
	make -C $(MLX_PATH) clean
	rm -rf $(OBJ_PATH) $(MLX_LIB) 

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
