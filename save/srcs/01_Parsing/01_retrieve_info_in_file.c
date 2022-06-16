#include "cub3d.h"

/**
 * @brief Get the path of texture object
 * 			Steps:
 * 			1) If there are any spaces or tabs, just ignore them 
 * 			2) Count in advance the total length of the path for the malloc
 * 			3) Copy the path into the newly malloced var until you encounter a 
 * 			   space/tab/newline
 * 			4) Check if there are any alphanum chars (even dots or slashes) 
 * 			   after => should it be the case, return NULL
 * 			5) return the path
 * 
 * 			/!\ Why malloc "len - j + 1"? Because len does not begin at 0, so we
 * 				must substract j to have the correct count.
 
 * @param line (Ex: "EA         ./path_to_the_east_texture  ")
 * @param j Begins after the two letters of the direction 
 * 			\("    ./path_to_the_east_texture  ")
 * @return char* - Returns the true path, devoid of any whitespaces , or NULL if
 * 		   it is invalid \("./path_to_the_east_texture") 
 */
static char	*get_path_of_texture(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' '  && line[len] != '\t'))
		len++;
	path = (char *)malloc(sizeof(char) * (len - j + 1)); 
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

/**
 * @brief Get the rgb colors object
 * 			Steps:
 * 			1) Split the line (i.e "      225,30,0") on the commas
 * 			2) Convert the strings (i.e ["  225", "30", "0"]) into ints 
 * 			   using atoi (which manages the whitespaces on its own)
 * 			3) If there are more than 3 numbers, return an error
 *
 * @param line To bypass the letter at the beginning, we sent line + j + 1
 * @return int* - the array of 3 ints (r, g, b)
 */
static int	*get_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		i;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_double_array(rgb_to_convert);
		return (0);
	}
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
		return (0);
	i = 0;
	while (rgb_to_convert[i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1)
			return (0);
		i++;
	}
	free_double_array(rgb_to_convert);
	return (rgb);
}

// if (line[j + 2] && ft_isprint(line[j + 2]))  
// cas où la ligne c'est : SOU ./path_to_the_south_texture
static int	fill_in_the_correct_dir(t_graphics *graph, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2])) 
		return (ERR);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(graph->dir_NO))
		graph->dir_NO = get_path_of_texture(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(graph->dir_SO))
		graph->dir_SO = get_path_of_texture(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(graph->dir_WE))
		graph->dir_WE = get_path_of_texture(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(graph->dir_EA))
		graph->dir_EA = get_path_of_texture(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

// if (line[j + 1] && ft_isprint(line[j + 1]))  
// cas où la ligne c'est : FLOOR 220,100,0 au lieu de F 220,100,0
static int fill_in_the_floor_or_ceiling(t_graphics *graph, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1])) 
		return (ERR);
	if (!graph->ceiling && line[j] == 'C')
	{
		graph->ceiling = get_rgb_colors(line + j + 1);
		if (graph->ceiling == 0)
			return (ERR);
	}
	else if (!graph->floor && line[j] == 'F')
	{
		graph->floor = get_rgb_colors(line + j + 1);
		if (graph->floor == 0)
			return (ERR);
	}
	else
		return (ERR);
	return (SUCCESS);
}

int	ignore_whitespaces_and_get_info(t_data *data, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1]) && !ft_isdigit(map[i][j]))
		{
			if (fill_in_the_correct_dir(&data->graphics, map[i], j) == ERR)
				return (print_error(MSG_DIRECTION));
			return (BREAK);
		}	
		else
		{
			if (fill_in_the_floor_or_ceiling(&data->graphics, map[i], j) == ERR)
				return (print_error(MSG_FLOOR_CEILING));
			return (BREAK);
		}	
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (retrieve_map_description(data, map, i) == FAILURE)
			return (print_error(MSG_INVALID_MAP));
		return (SUCCESS);
	}
	return (CONTINUE);
}

// tricks du return (CONTINUE) qui n'est pas verbalisé donc ca continue la
// boucle sans la break par un return
int	retrieve_info_in_file(t_data *data, char **map)
{
	int	i;
	int	j;
	int ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = ignore_whitespaces_and_get_info(data, map, i ,j);
			if (ret == BREAK)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
