#include "../../cub3d.h"

static void	load_texture(t_data *data, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(
			data->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		exit(1);
	tex->addr = (int *)mlx_get_data_addr(
			tex->img, &tex->bpp, &tex->line_len, &tex->endian);
}

void	load_all_textures(t_data *data)
{
	load_texture(data, &data->tex[TEX_NO], data->no);
	load_texture(data, &data->tex[TEX_SO], data->so);
	load_texture(data, &data->tex[TEX_WE], data->we);
	load_texture(data, &data->tex[TEX_EA], data->ea);
}
