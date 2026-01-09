#include "../../cub3d.h"

int	parse_tex(char **dst, char *s)
{
	int		i;
	int		end;
	int		start;
	char	*path;

	if (*dst)
		return (err("Duplicate texture"));
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	start = i;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	end = i;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i])
		return (err("Invalid texture path"));
	path = ft_substr(s, start, end - start);
	if (!path || access(path, R_OK))
		return (free(path), err("Invalid texture path"));
	*dst = path;
	return (0);
}
