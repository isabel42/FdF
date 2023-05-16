SRCS	= main.c \
			map.c \
			map_column.c \
			iso.c \
			get_next_line_utils.c \
			get_next_line.c  \
			segment.c \
			tracer_segment.c

OBJS 	= ${SRCS:.c=.o}

NAME 	= fdf

FT_NAME = ./libft/libft.a

MLX_NAME = ./minilibx/libmlx.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wextra -Wall -Werror

INCLUDE = -I./libft/ -I./minilibx/ -I.

.c.o:	
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS} ${FT_NAME} ${MLX_NAME}
			${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} -L./minilibx/ -lmlx -L./libft/ -lft -framework OpenGL -framework AppKit -lm -g

all:		${NAME}

${FT_NAME}:
	make bonus -C ./libft/

${MLX_NAME}:
	make -C ./minilibx

clean:
			make clean -C ./libft
			make clean -C ./minilibx	
			${RM} ${OBJS}

fclean: 	clean
			make fclean -C ./libft
			${RM} ${MLX_NAME}
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re