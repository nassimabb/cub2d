/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:13:45 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/16 19:37:38 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	const	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dest == 0)
		return (NULL);
	ft_strcpy((char *)dest, (char *)src);
	return ((char *)dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		l1;
	int		i;
	char	*p;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	l1 = ft_strlen(s1);
	i = -1;
	p = malloc(sizeof(char *) * (l1 + ft_strlen(s2)));
	if (!p)
		return (NULL);
	while (s1[++i] != '\0')
	{
		p[i] = s1[i];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		p[i + l1] = s2[i];
		i++;
	}
	p[i + l1] = '\0';
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	if (s)
	{
		while (s[len] != '\0')
			len++;
	}
	return (len);
}
