SRCS	= main.c 

OBJS 	= ${SRCS:.c=.o}

NAME 	= fdf

LIB		= libfdf.a

CC		= gcc

RM		= rm -f

AR		= ar rc

CFLAGS	= -Wextra -Wall -Werror

.c.o:	
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
				make bonus -C ./libft
				make -C ./minilibx
				cp ./libft/libft.a ${LIB}
				cp ./minilibx/libmlx.a ${LIB}
				${AR} ${LIB} ${OBJS}
				ranlib ${LIB}
			${CC} ${CFLAGS} -o ${NAME} main.c -L. -lfdf -framework OpenGL -framework AppKit -lm

all:		${NAME}

clean:
			make fclean -C ./libft	
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re