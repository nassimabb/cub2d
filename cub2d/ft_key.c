/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:22:36 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/18 14:31:06 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			key_press_hook(int keycode, void *ptr)
{
	ptr = NULL;
	if (keycode == EXIT_KEY)
		exit(1);
	if (keycode == KEY_UP)
		nassim.walkdirection = 1;
	if (keycode == KEY_DOWN)
		nassim.walkdirection = -1;
	if (keycode == KEY_RIGHT)
		nassim.turndirection = 1;
	if (keycode == KEY_LEFT)
		nassim.turndirection = -1;
    if (keycode == W)
		nassim.walkdirection = 1; // walkDirection
	if (keycode == S)
		nassim.walkdirection = -1;
	if (keycode == D)
		nassim.turndirection = 1; // turnDirection
	if (keycode == A)
		nassim.turndirection = -1;
	return (1);
}

int			key_release_hook(int keycode, void *ptr)
{
	ptr = NULL;
	if (keycode == KEY_UP)
		nassim.walkdirection = 0;
	if (keycode == KEY_DOWN)
		nassim.walkdirection = 0;
	if (keycode == KEY_RIGHT)
		nassim.turndirection = 0;
	if (keycode == KEY_LEFT)
		nassim.turndirection = 0;
    if (keycode == W)
		nassim.walkdirection = 0; // walkDirection
	if (keycode == S)
		nassim.walkdirection = 0;
	if (keycode == D)
		nassim.turndirection = 0; // turnDirection
	if (keycode == A)
		nassim.turndirection = 0;
	return (1);
}