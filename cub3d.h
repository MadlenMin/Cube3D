#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}		t_keys;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}		t_color;

typedef struct s_texture
{
	void		*img;
	int			*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}		t_texture;

typedef struct s_data
{
	char		**map;
	int			map_h;
	int			map_w;

	int			px;
	int			py;
	char		dir;

	char		*no;
	char		*so;
	char		*we;
	char		*ea;

	int			floor;
	int			ceiling;
	t_color		floor_color;
	t_color		ceiling_color;

	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;

	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	double		move_speed;
	double		rot_speed;

	t_keys		keys;

	t_texture	tex[4];

	double		old_time;
}		t_data;

/* Parser */
int		parse(int fd, t_data *d, int map_started, int cfg);
int		parse_color(int *dst, char *s);
int		parse_tex(char **dst, char *s);
char	**map_add(char **m, char *l);
int		validate_map(t_data *d);
int		is_map_char(char c);
int		is_map_line(char *l);
void	trim_nl(char *s);
int		err(char *msg);

/* Utils */
void	ft_free(char **arr);
char	**ft_dup_split(char **map);
void	free_data(t_data *data);

/* MLX / Game */
void	start(t_data *data);
void	init(t_data *data);
void	load_all_textures(t_data *data);
void	init_hooks(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		close_window(t_data *data);
int		render_frame(t_data *data);
void	assign_direction(t_data *d);

/* Movement */
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

/* Rendering */
void	raycasting(t_data *data);

#endif
