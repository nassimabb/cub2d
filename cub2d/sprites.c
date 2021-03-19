/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:09:44 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/19 16:11:00 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

float			ft_distancebetweenpoints(float x1, float y1, float x2, float y2)
{
	return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
float	distance(float x1, float y1, float x2, float y2)
{
	return (hypotf((x2 - x1), (y2 - y1)));
}

void			render_spt(int x, int y, int sp_size, int k)
{
	int			color;
	int			i;
	int			j;

	i = 0;
	color = 0;
	while (i++ < sp_size)
	{
		if (x + i < 0 || x + i > game_data.resolution_x)
			continue;
		if (g_s_data[k].distance >= g_ray_distance[x + i])
			continue;
		j = 0;
		while (j++ < sp_size)
		{
			if ((int)(g_sprite.height * (j * g_sprite.width / sp_size) +
			(i * g_sprite.height / sp_size)) < g_sprite.width * g_sprite.height)
				color = g_sprite.data[(int)(g_sprite.height *
				(j * g_sprite.width / sp_size) +
				(i * g_sprite.height / sp_size))];
			if (color != 0)
				my_mlx_pixel_put(&img, x + i, y + j, color);
		
		
		}
	}
}

void			 ft_sprite(int i)
{
	float		sp_size;
	float		x_inter;
	float		y_inter;
	float		sp_angle;

	// 
	sp_angle = atan2(g_s_data[i].y - nassim.y, g_s_data[i].x - nassim.x);
	while (sp_angle - nassim.dirangle > M_PI)
		sp_angle -= 2 * M_PI;
	while (sp_angle - nassim.dirangle < -M_PI)
		sp_angle += 2 * M_PI;
	if (game_data.resolution_y > game_data.resolution_x)
		sp_size = (game_data.resolution_y /g_s_data[i].distance) * TILE_SIZE;
	else
		sp_size = (game_data.resolution_x /g_s_data[i].distance) * TILE_SIZE;
	y_inter = game_data.resolution_y / 2 - sp_size / 2;
	x_inter = (sp_angle - nassim.dirangle) /
	FOV_ANGLE * game_data.resolution_x + (game_data.resolution_x / 2 - sp_size / 2);
	render_spt(x_inter, y_inter, sp_size, i);
}

void			ft_sort_sprites(void)
{
	// sort sprites 	
	int			i;
	int			j;
	t_sprites	temp;

	i = 0;
	while (i < game_data.nb_of_sprites)
	{
		j = 0;
		while (j < game_data.nb_of_sprites - 1)
		{
			if (g_s_data[j].distance < g_s_data[j + 1].distance)
			{
				temp = g_s_data[j];
				g_s_data[j] = g_s_data[j + 1];
				g_s_data[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void			init_sprites_pos(void)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	// loop ela number dyal sprites
	while (map[i] != '\0' && k < game_data.nb_of_sprites)
	{
		j = 0;
		while (map[i][j] != '\0' && k < game_data.nb_of_sprites)
		{
			if (map[i][j] == '2')
			{
				// itialise sprite position
				g_s_data[k].x = (i + 0.5) * TILE_SIZE;
				g_s_data[k].y = (j + 0.5) * TILE_SIZE;
				k++;
			}
			j++;
		}
		i++;
	}
}

// cALL IN UPDATE  ()
void			ft_draw_sprites(void)
{
	int			i;

	i = 0;
	// loop ela nbr dyal sprites
	while (i < game_data.nb_of_sprites)
	{
		// kan 7ssb distance (payerx, player y, spritex, sprite y)
		g_s_data[i].distance = distance(nassim.x, nassim.y ,g_s_data[i].x, g_s_data[i].y);
		i++;
	}
	ft_sort_sprites();
	i = 0;
	// draw each sprite 
	while (i < game_data.nb_of_sprites)
		ft_sprite(i++);
}
 
void			init_sprites(void)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	// map[][] 
	while (map[i] != '\0')
	{
		j = 0;
		// count number of sprites
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '2')
				game_data.nb_of_sprites += 1;
			j++;
		}
		i++;
	}
	// distance beween player and sprite
	init_sprites_pos();
}
