/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 21:59:45 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:46:12 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrev(char *str)
{
	int		len;
	int		i;
	char	*new;

	len = ft_strlen(str);
	new = malloc(len);
	i = -1;
	while (++i < len)
		new[i] = str[len - i - 1];
	return (new);
}
