#include "../../cub3d.h"

static int	check_player(t_data *d)
{
	int	x;
	int	y;
	int	p;

	p = 0;
	y = 0;
	while (d->map[y])
	{
		x = 0;
		while (d->map[y][x])
		{
			if (ft_strchr("NSEW", d->map[y][x]))
			{
				d->px = x;
				d->py = y;
				d->dir = d->map[y][x];
				p++;
			}
			x++;
		}
		y++;
	}
	if (p != 1)
		return (err("Map must have exactly one player"));
	return (0);
}

static int	check_chars_and_borders(t_data *d)
{
	int	x;
	int	y;
	int	width;
	int	height;

	height = 0;
	while (d->map[height])
		height++;
	y = 0;
	while (y < height)
	{
		width = ft_strlen(d->map[y]);
		x = 0;
		while (x < width)
		{
			if (!is_map_char(d->map[y][x]))
				return (err("Invalid character in map"));
			if ((y == 0 || y == height - 1 || x == 0 || x == width - 1)
				&& d->map[y][x] != '1' && d->map[y][x] != ' ')
				return (err("Map border must be walls or spaces"));
			x++;
		}
		y++;
	}
	return (0);
}

static int	flood(char **map, int x, int y, int height)
{
	if (y < 0 || x < 0 || y >= height || !map[y]
		|| !map[y][x] || map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (0);
	map[y][x] = 'F';
	return (flood(map, x + 1, y, height)
		|| flood(map, x - 1, y, height)
		|| flood(map, x, y + 1, height)
		|| flood(map, x, y - 1, height));
}

int	validate_map(t_data *d)
{
	char	**cpy;
	int		height;

	height = 0;
	while (d->map[height])
		height++;
	if (check_chars_and_borders(d))
		return (1);
	if (check_player(d))
		return (1);
	if (fill_map_spaces(&d->map))
		return (err("Error\nMemory Error\n"));
	cpy = ft_dup_split(d->map);
	if (!cpy)
		return (err("Memory error"));
	if (flood(cpy, d->px, d->py, height))
	{
		ft_free(cpy);
		return (err("Map not closed - player can escape"));
	}
	ft_free(cpy);
	return (0);
}
