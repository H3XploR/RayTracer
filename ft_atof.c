/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:19:17 by yantoine          #+#    #+#             */
/*   Updated: 2025/02/18 17:22:12 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline static char	*check_sign(char *str, int *sign)
{
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	return (str);
}

float	ft_atof(char *str)
{
	float	res;
	float	dec;
	int		sign;

	res = 0;
	dec = 0;
	sign = 1;
	str = check_sign(str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			dec = dec * 10 + *str - '0';
			str++;
		}
	}
	return (sign * (res + dec / pow(10, ft_strlen(str))));
}
