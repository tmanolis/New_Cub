#include "cub3d.h"

// Récupérer le nombre de lignes dans le fichier .ber
static int	retrieve_line_number(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		printf("\e[31mError: open failed\e[0m\n");
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
	}
	close(fd);
	return (line_count);
}

static void	put_input_in_map(int row, int column, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->map.fd);
	while (line != NULL)
	{
		data->map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->map.file[row])
			return (free_double_array(data->map.file));
		while (line[i] != '\0')
			data->map.file[row][column++] = line[i++];
		data->map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(data->map.fd);
	}
	data->map.file[row] = NULL;
}

void	create_map_from_cub_file(char *path, t_data *data)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	data->map.line_count = retrieve_line_number(path);
	data->map.path = path;
	data->map.file = ft_calloc(data->map.line_count + 1, sizeof(char *));
	if (!(data->map.file))
		return ;
	data->map.fd = open(path, O_RDONLY);
	if (data->map.fd < 0)
		printf("\e[31mError: open failed\e[0m\n");
	else
	{
		put_input_in_map(row, column, i, data);
		close(data->map.fd);
	}
}