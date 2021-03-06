/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:23:15 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 17:23:38 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_a_white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (FAILURE);
	else
		return (SUCCESS);
}

int	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (FAILURE);
}
