/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:18:24 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/03 15:44:12 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

static int		count_worlds(char const *s, char *c)
{
	int a;
	int count;

	count = 0;
	a = 0;
	while (s[a] != '\0')
	{
		if (!ft_strchr(c, s[a]) && (ft_strchr(c, s[a - 1]) || a == 0))
			count++;
		a++;
	}
	return (count);
}

static char		*worlds(char const *s, char *c, int *len, char *world)
{
	int a;
	int b;

	b = 0;
	while (ft_strchr(c, s[(*len)]) && s[(*len)++])
		;
	while (!ft_strchr(c, s[b + *len]) && s[*len + b++])
		;
	world = malloc(b + 1);
	if (!world)
		return (0);
	a = 0;
	while (!ft_strchr(c, s[(*len)]) && s[(*len)])
		world[a++] = s[(*len)++];
	world[a] = 0;
	return (world);
}

char			**ft_strstrsplit(char const *s, char *c)
{
	char	**new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = 0;
	if (s)
		new_str = malloc(sizeof(*new_str) * count_worlds(s, c) + 1);
	if (!new_str)
		return (0);
	while (i < count_worlds(s, c))
	{
		new_str[i] = worlds(s, c, &j, new_str[i]);
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
