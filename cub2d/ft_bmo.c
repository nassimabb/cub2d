/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:20:25 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/17 12:33:01 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char	g_bmpfileheader[14];
unsigned char	g_bmpinfoheader[40];
int				g_fd;
int				g_filesize;

void			ft_set_header(void)
{
	int			i;

	i = 2;
	g_bmpfileheader[0] = 'B';
	g_bmpfileheader[1] = 'M';
	while (i < 10)
		g_bmpfileheader[i++] = 0;
	g_bmpfileheader[i++] = 54;
	while (i < 14)
		g_bmpfileheader[i++] = 0;
}

void			ft_set_infoheader(void)
{
	int			i;

	i = 0;
	g_bmpinfoheader[i++] = 40;
	while (i < 12)
		g_bmpinfoheader[i++] = 0;
	g_bmpinfoheader[i++] = 1;
	g_bmpinfoheader[i++] = 0;
	g_bmpinfoheader[i++] = 24;
	g_bmpinfoheader[i] = 0;
}

void			ft_right_shift(void)
{
	g_fd = open("file.bmp", O_CREAT | O_RDWR, 0644);
	g_filesize = 54 + 3 * (game_data.resolution_x * game_data.resolution_y);
	g_bmpfileheader[2] = (unsigned char)g_filesize;
	g_bmpfileheader[3] = (unsigned char)(g_filesize >> 8);
	g_bmpfileheader[4] = (unsigned char)(g_filesize >> 16);
	g_bmpfileheader[5] = (unsigned char)(g_filesize >> 24);
	g_bmpinfoheader[4] = (unsigned char)(game_data.resolution_x);
	g_bmpinfoheader[5] = (unsigned char)(game_data.resolution_x >> 8);
	g_bmpinfoheader[6] = (unsigned char)(game_data.resolution_x >> 16);
	g_bmpinfoheader[7] = (unsigned char)(game_data.resolution_x >> 24);
	g_bmpinfoheader[8] = (unsigned char)(game_data.resolution_y);
	g_bmpinfoheader[9] = (unsigned char)(game_data.resolution_y >> 8);
	g_bmpinfoheader[10] = (unsigned char)(game_data.resolution_y >> 16);
	g_bmpinfoheader[11] = (unsigned char)(game_data.resolution_y >> 24);
	write(g_fd, g_bmpfileheader, 14);
	write(g_fd, g_bmpinfoheader, 40);
}

void			ft_to_bmp(void)
{
	int			i;
	int			j;
	int			num;

	i = 0;
	j = 0;
	num = 0;
	while (i < game_data.resolution_y)
	{
		num = (game_data.resolution_y - i - 1) * game_data.resolution_x;
		j = 0;
		while (j < game_data.resolution_x)
		{
			write(g_fd, &dst[num + j], 3);
			j++;
		}
		i++;
	}
	close(g_fd);
}

void			ft_handle_bmp(void)
{
	ft_set_header();
	ft_set_infoheader();
	ft_right_shift();
	ft_to_bmp();
	//ft_free(0, "Image Saved Successfully !");
}
