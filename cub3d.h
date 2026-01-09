#ifndef CUB3D_H
# define CUB3D_H

# define W 1280
# define H 1024
# define MAP_W 24
# define MAP_H 24

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"

# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>

// typedef struct s_data
// {
// 	char    *no;
// 	char    *so;
// 	char    *we;
// 	char    *ea;
// 	int     floor;
// 	int     ceiling;
// 	void	*mlx;
// 	void	*win;
// 	void	*img;
// 	char	**map;
// 	int		x_p;
// 	int		y_p;
// 	int		map_x;//?
// 	int		map_y;//?
// }				t_data;

typedef struct s_data
{
	char    *no;
	char    *so;
	char    *we;
	char    *ea;
	int     floor;
	int     ceiling;
	char    **map;
	int     map_h;
	int     map_w;
	int     px;
	int     py;
	char    pdir;
}	t_data;


int		parse(int fd, t_data *d);
int		parse_color(int *dst, char *s);
int		parse_tex(char **dst, char *s);
char	**map_add(char **m, char *l);
int		err(char *msg);
void	trim_nl(char *s);
int		is_map_char(char c);
int		is_map_line(char *l);
// int		validate_map(t_data *d);
// void    start(t_data *data);
void	free_data(t_data *data);
void	init(t_data *data);
void	ft_free(char **arr);

#endif