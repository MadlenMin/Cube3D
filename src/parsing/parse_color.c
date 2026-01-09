#include "../../cub3d.h"

static void	remove_spaces(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			s[j++] = s[i];
		i++;
	}
	s[j] = 0;
}

static int	numeric(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	parse_color(int *dst, char *s)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	char	*tmp;

	if (*dst != -1)
		return (err("Duplicate color"));
	tmp = ft_strdup(s);
	if (!tmp)
		return (err("Malloc failed"));
	remove_spaces(tmp);
	rgb = ft_split(ft_strdup(tmp), ',');
	free(tmp);
	if (!rgb || ft_arrlen(rgb) != 3)
		return (err("Invalid color format"));
	if (!numeric(rgb[0]) || !numeric(rgb[1]) || !numeric(rgb[2]))
		return (ft_free(rgb), err("Invalid color format"));
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (err("Color out of range"));
	return (*dst = (r << 16) | (g << 8) | b, 0);
}
