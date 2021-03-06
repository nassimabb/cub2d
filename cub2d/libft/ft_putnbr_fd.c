/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 03:00:18 by nabboudi          #+#    #+#             */
/*   Updated: 2019/10/30 03:00:49 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int newvar;

	newvar = n;
	if (n < 0)
	{
		newvar = -n;
		ft_putchar_fd('-', fd);
	}
	if (newvar <= 9)
	{
		ft_putchar_fd(newvar + 48, fd);
	}
	if (newvar > 9)
	{
		ft_putnbr_fd(newvar / 10, fd);
		ft_putchar_fd(newvar % 10 + 48, fd);
	}
}
