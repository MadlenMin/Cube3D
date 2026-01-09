#include "cub3d.h"

void	init(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->floor = -1;
	data->ceiling = -1;
	data->map = NULL;
	data->map_h = 0;
	data->map_w = 0;
	data->px = -1;
	data->py = -1;
	data->dir = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (printf("Error. Wrong Input\n"), 1);
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
		return (printf("Error. Wrong File Type\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), 1);
	init(&data);
	if (!parse(fd, &data, 0, 0))
		return (free_data(&data), close(fd), 1);
	close(fd);
	//start(&data);
	free_data(&data);
}
