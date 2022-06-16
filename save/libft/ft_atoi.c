/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:38:43 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/26 20:00:42 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	n;
	int	i;

	result = 0;
	n = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		 || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -n;
		i++;
	}
	if (str[i] && str[i] == '\n')
		return (-1);
	while (str[i] > 47 && str[i] < 58)
		result = result * 10 + (str[i++] - 48);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	if (str[i] && (str[i] <= 47 || str[i] >= 58))
		return (-1);
	return (result * n);
}
