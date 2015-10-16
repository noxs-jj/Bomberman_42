/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newstrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 22:15:31 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:39:48 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_newstrchr(char *str, char c)
{
	int		len;
	char	*new;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	new = ft_strnew(len + 1);
	ft_memcpy(new, str, len);
	new[len + 1] = 0;
	return (new);
}
