SRCS			=	srcs/ft_init.c 				\
					srcs/ft_update.c 			\
					srcs/vect.c 				\
					srcs/ft_key.c 				\
					srcs/sprite.c				\
					config/config.c 			\
					config/get_map.c 			\
					config/util.c 				\
					gnl/get_next_line.c 		\
					gnl/get_next_line_utils.c 	\
					bmp/bmp.c 					\
					srcs/main.c

NAMELIB			= ./libft/libft.a
OBJS			= $(SRCS:.c=.o)
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra
MLX				=  -lmlx -framework OpenGL -framework AppKit


NAME			= cub3D

BMP				= cub3D.bmp

all:			$(NAME)

$(NAME):		$(OBJS)
				$(MAKE) -C ./libft
				$(MAKE) bonus -C ./libft
				$(CC)  $(OBJS)  $(NAMELIB)  $(MLX) -o $(NAME) 
				


clean:
	$(RM) $(OBJS)
	$(MAKE) fclean -C ./libft

fclean:	clean
	@$(RM) $(NAME)  $(BMP)
	$(MAKE) fclean -C ./libft
	

re:	fclean $(NAME)