SRCS	=	main.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
NAME	=	fdf
CFLAGS	=	-Wall -Wextra -g minilibx/libmlx.a -I includes -Iminilibx -lX11 -lXext

gcc main.c minilibx/libmlx_Linux.a -I includes -I minilibx -lX11 -lXext -o fdf

rm		=	rm -f

.PHONY:		all
all:		$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

