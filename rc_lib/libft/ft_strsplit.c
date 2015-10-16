/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:18:24 by rcargou           #+#    #+#             */
/*   Updated: 2014/11/08 11:36:36 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int		count_worlds(char const *s, char c)
{
	int a;
	int count;

	count = 0;
	a = 0;
	while (s[a] != '\0')
	{
		if (s[a] != c && (s[a - 1] == c || a == 0))
			count++;
		a++;
	}
	return (count);
}

static char		*worlds(char const *s, char c, int *len, char *world)
{
	int a;
	int b;

	b = 0;
	while (s[(*len)] == c && s[(*len)++])
		;
	while (s[b + *len] != c && s[*len + b++])
		;
	world = malloc(b + 1);
	if (!world)
		return (0);
	a = 0;
	while (s[(*len)] != c && s[(*len)])
		world[a++] = s[(*len)++];
	world[a] = 0;
	return (world);
}

char			**ft_strsplit(char const *s, char c)
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
