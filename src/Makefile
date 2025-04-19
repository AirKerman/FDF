SRCS	=	 main.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
NAME	=	fdf
CFLAGS	=	-I includes -I minilibx
MLXFLAG	=	-L minilibx -lmlx -lmlx_Linux -lX11 -lXext

rm		=	rm -f

.PHONY:		all
all:		$(NAME)

.PHONY:		clean
clean:		
			$(RM) $(OBJS)
			make clean -C /minilibx/

.PHONY:		fclean
fclean:
			$(RM) $(OBJS) $(NAME)



.PHONY:		re
re:			fclean $(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(MLXFLAG)
			make -C /minilibx/

