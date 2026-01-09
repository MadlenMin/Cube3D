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