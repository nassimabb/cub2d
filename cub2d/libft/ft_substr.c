/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 03:08:42 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/16 19:17:10 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	p = malloc(len + 1);
	if (p == NULL)
		return (0);
	while (len--)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	free(s);
	return (char *)(p);
}
