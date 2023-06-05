
	// Gestion des quotes
	if (line[i] == 34)
		{
			while (line[i] != 34)
			{
				new[x] = line[i];
				x++;
				i++;
			}
		}
		else if (line[i] == 39)
		{
			while (line[i] != 39)
			{
				new[x] = line[i];
				x++;
				i++;
			}
		}
		else


//test
while (line[i] != 124 && line[i] != 62 && line[i] != 60 && line[i] != 39 && line[i] != 34)
		{
			new[x] = line[i];
			x++;
			i++;
		}
		new[x] = 32;
		x++;
		while (line[i] == 124 || line[i] == 62 || line[i] == 60 || line[i] == 39 || line[i] == 34)
		{
			new[x] = line[i];
			x++;
			i++;
		}
		new[x] = 32;


//fonction de split
char	*f_place_space(char *line)
{
	int		i;
	int		x;
	int		sing_quotes;
	int		dou_quotes;
	char	*new;

	i = 0;
	x = 0;
	dou_quotes = 0;
	sing_quotes = 0;
	new = ft_calloc(sizeof(char), ft_strlen(line));
	if (!new)
		return (NULL);
	while (line[i])
	{
		while (line[i] <= 32)
			i++;
		while (line[i] > 32)
		{
			if (line[i] == 124)
			{
				printf("in=%s\n", new);
				new[x] = 32;
				new[x++] = line[i++];
				new[x++] = 32;
			}
			else
			{
				new[x] = line[i];
				x++;
				i++;
			}
		}
		new[x++] = 32;
	}
	return (new);
}