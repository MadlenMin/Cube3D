#include "../../cub3d.h"

char	**map_add(char **m, char *l)
{
	int		i;
	char	**n;

	i = 0;
	while (m && m[i])
		i++;
	n = malloc(sizeof(char *) * (i + 2));
	if (!n)
		return (NULL);
	i = 0;
	while (m && m[i])
	{
		n[i] = m[i];
		i++;
	}
	n[i++] = ft_strdup(l);
	n[i] = NULL;
	free(m);
	return (n);
}

int	fill_map_check(char ***map_ptr, int *max, char ***result)
{
	char	**map;
	int		y;
	int		width;
	int		max_width;

	if (!map_ptr || !*map_ptr)
		return (1);
	map = *map_ptr;
	max_width = 0;
	y = 0;
	while (map[y])
	{
		width = ft_strlen(map[y]);
		if (width > max_width)
			max_width = width;
		y++;
	}
	*max = max_width;
	*result = malloc(sizeof(char *) * (y + 1));
	if (!*result)
		return (1);
	return (0);
}

void	fill_map_loop(char **map, char **result, int max_width, int y)
{
	int	x;
	int	len;

	len = ft_strlen(map[y]);
	x = 0;
	while (x < max_width)
	{
		if (x < len && map[y][x] != ' ')
			result[y][x] = map[y][x];
		else
			result[y][x] = '0';
		x++;
	}
	result[y][max_width] = '\0';
}

int	fill_map_spaces(char ***map_ptr)
{
	int		y;
	int		max_width;
	char	**result;
	char	**map;

	if (fill_map_check(map_ptr, &max_width, &result))
		return (1);
	map = *map_ptr;
	y = 0;
	while (map[y])
	{
		result[y] = malloc((size_t)max_width + 1);
		if (!result[y])
		{
			result[y] = NULL;
			ft_free(result);
			return (1);
		}
		fill_map_loop(map, result, max_width, y);
		y++;
	}
	result[y] = NULL;
	ft_free(map);
	*map_ptr = result;
	return (0);
}
