/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:25:51 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 17:25:56 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks whether the arg given is a correct .ber extension, exists, and
 * 			isn't a folder instead of a file.
 * 
 * @param arg path of the file
 * @return int 0 for SUCCESS and 1 for FAILURE
 */
int	check_arg(char *arg)
{
	size_t	len;
	int		fd;

	len = ft_strlen(arg);
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (FAILURE);
	}
	else
	{
		fd = open(arg, O_RDONLY);
		close(fd);
		if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
				|| arg[len - 1] != 'b'
				|| arg[len - 4] != '.') || fd < 0)
			return (FAILURE);
		else
			return (SUCCESS);
	}
}
