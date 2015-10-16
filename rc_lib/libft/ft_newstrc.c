/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newstrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 16:15:23 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:39:30 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_newstrc(char *s, char c)
{
	int			len;
	char		*new;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	new = malloc(len + 1);
	new = strncpy(new, s, len);
	new[len] = 0;
	return (new);
}
