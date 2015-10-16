/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 15:12:23 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:41:49 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strbchr(char *str, char c)
{
	int i;

	i = ft_strlen(str) - 1;
	while (i)
	{
		if (str[i] == c)
			return (&(str[i + 1]));
		i--;
	}
	return (&(str[i]));
}
