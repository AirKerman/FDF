SRCS	=	 main.c utils/get_next_line.c utils/gnl_utils.c utils/ft_split.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
NAME	=	fdf
CFLAGS	=	-I includes -I minilibx -g
MLXFLAG	=	-L minilibx -lm -lmlx -lmlx_Linux -lX11 -lXext

rm		=	rm -f

.PHONY:		all
all:		$(NAME)

.PHONY:		clean
clean:		
			$(RM) $(OBJS)
			make clean -C minilibx/

.PHONY:		fclean
fclean:		clean
			$(RM) $(NAME)



.PHONY:		re
re:			fclean $(NAME)

$(NAME):	$(OBJS)
			make -C minilibx/
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(MLXFLAG)

