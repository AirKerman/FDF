SRCS	=	 main.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
NAME	=	fdf
CFLAGS	=	-I includes -I minilibx
MLXFLAG	=	-L minilibx -lmlx -lmlx_Linux -lX11 -lXext
# gcc main.c minilibx/libmlx_Linux.a -I includes -I minilibx -lX11 -lXext -o fdf

rm		=	rm -f

.PHONY:		all
all:		$(NAME)

$(EXEC):	
			

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(MLXFLAG)

