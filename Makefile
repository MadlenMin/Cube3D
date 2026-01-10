NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLX_PATH = mlx/

MLX_LIB = $(MLX_PATH)libmlx.a

MLX_FLAGS = -lmlx -L$(MLX_PATH) -lXext -lX11 -lm -lz # for Linux
# MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

LIBFT_PATH = libft/

GNL_PATH = get_next_line/

LIBFT_LIB = $(LIBFT_PATH)libft.a

CFILES = main.c $(wildcard src/*/*.c) # POXEL --------------------------------------------------

GNL_FILES = $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c

OBJECTS = $(CFILES:.c=.o) $(GNL_FILES:.c=.o)

all: subsystems $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I$(MLX_PATH) -c  $< -o $@

subsystems:
	@make -C $(MLX_PATH) all
	@make -C $(LIBFT_PATH) all

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -I$(MLX_PATH) $(OBJECTS) $(MLX_LIB) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	rm -f $(OBJECTS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

norm:
	norminette get_next_line libft $(CFILES)

.PHONY: all clean fclean re norm