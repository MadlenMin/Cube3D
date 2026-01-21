NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

MLX_PATH = mlx/

MLX_LIB = $(MLX_PATH)libmlx.a

MLX_FLAGS = -lmlx -L$(MLX_PATH) -lXext -lX11 -lm -lz  # for Linux
# MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

LIBFT_PATH = libft/

GNL_PATH = get_next_line/

LIBFT_LIB = $(LIBFT_PATH)libft.a

CFILES = main.c                        \
		 src/free/free.c               \
		 src/game/textures.c           \
		 src/parsing/map_v_utils.c     \
		 src/parsing/parse_map.c       \
		 src/ray_casting/dda.c         \
		 src/free/free_data.c          \
		 src/hook/hook.c               \
		 src/parsing/map_validate.c    \
		 src/parsing/parse_texture.c   \
		 src/ray_casting/helper.c      \
		 src/game/directions.c         \
		 src/movement/movement.c       \
		 src/parsing/parse_color.c     \
		 src/parsing/parse_utils.c     \
		 src/ray_casting/put_wall.c    \
		 src/game/start.c              \
		 src/movement/rotate.c         \
		 src/parsing/parse_file.c      \
		 src/ray_casting/calculs.c     \
		 src/ray_casting/raycasting.c  

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