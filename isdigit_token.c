#include "miniRT.h"

int	isdigit_token(char **tokens)
{
	int	i;
	int	j;

	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			if (!ft_isdigit(tokens[i][j]) && tokens[i][j] != '\n' && tokens[i][j] != '-' && tokens[i][j] != ',')
			{
				printf("%c\n", tokens[i][j]);
				printf("%p\n", tokens[i]);
				return (0);
			}
		}
	}
	return (1);
}
