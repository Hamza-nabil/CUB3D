SRCS			=	main.c ft_init.c ft_update.c vect.c ft_key.c sprite.c\
					config/config.c config/get_map.c config/util.c \
					gnl/get_next_line.c gnl/get_next_line_utils.c 
OBJS			= $(SRCS:.c=.o)
CC				= gcc
RM				= rm -f
CFLAGS			=  -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm -L libft -lft
MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}
				

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
	@$(MAKE) -C mlx clean
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
	@$(RM) $(NAME) $(MLX)

re:	fclean $(NAME)