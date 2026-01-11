#include "../../cub3d.h"

void	free_data(t_data *data)
{
	int	i;

	if (data->mlx)
	{
		i = 0;
		while (i < 4)
			if (data->tex[i].img)
				mlx_destroy_image(data->mlx, data->tex[i++].img);
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
	}
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->map)
		ft_free(data->map);
}
