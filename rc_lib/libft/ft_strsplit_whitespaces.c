/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <tvallee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 14:51:18 by tvallee           #+#    #+#             */
/*   Updated: 2015/09/04 13:56:50 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isspace(char c)
{
	return ((ft_strchr("\t\n\v\f\r ", c)) ? 1 : 0);
}

static size_t	ft_countstr(char const *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!ft_isspace(s[i]) && s[i])
		{
			count++;
			i++;
		}
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (count);
}

char			**ft_strsplit_whitespaces(char const *s)
{
	t_delim	str;
	char	**r;
	size_t	nb;
	int		k;

	if (!s)
		return (NULL);
	nb = ft_countstr(s);
	r = malloc(sizeof(char *) * (nb + 1));
	str.i = 0;
	k = 0;
	while ((size_t)k < nb)
	{
		while (ft_isspace(s[str.i]))
			str.i++;
		str.j = str.i;
		while (s[str.j] && !ft_isspace(s[str.j]))
			str.j++;
		r[k] = ft_strsub(s, str.i, str.j - str.i);
		k++;
		str.i = str.j + 1;
	}
	r[k] = NULL;
	return (r);
}
