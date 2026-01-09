#include "../../cub3d.h"

static void	get_map_size(char **map, int *height, int *max_len)
{
	int	w;

	*height = 0;
	*max_len = 0;
	while (map[*height])
	{
		w = ft_strlen(map[*height]);
		if (w > *max_len)
			*max_len = w;
		(*height)++;
	}
}

static char	**dup_map(char **map, int height, int max_len)
{
	char	**dup;
	int		i;

	dup = (char **)malloc(sizeof(char *) * (height + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < height)
	{
		dup[i] = (char *)malloc(sizeof(char) * (max_len + 1));
		if (!dup[i])
		{
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		ft_strlcpy(dup[i], map[i], max_len + 1);
		while ((int)ft_strlen(dup[i]) < max_len)
			dup[i][ft_strlen(dup[i])] = ' ';
		dup[i][max_len] = '\0';
		i++;
	}
	dup[height] = NULL;
	return (dup);
}

char	**ft_dup_split(char **map)
{
	int	h;
	int	w;

	if (!map)
		return (NULL);
	get_map_size(map, &h, &w);
	return (dup_map(map, h, w));
}
