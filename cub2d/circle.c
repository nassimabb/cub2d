/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:53:08 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/14 17:32:07 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        ft_draw_texture(t_image ptr, int col, float offset, float wallstripheight)
{
    int start;
    int end;
    float   texture_y;
    int     color;
    int offset_x;
    int offset_y;
    int dist_from_top;
    start = (game_data.resolution_y / 2) - (wallstripheight / 2);
    end = (game_data.resolution_y / 2) + (wallstripheight / 2) ;
    texture_y = 0;
    offset_x = (ray.wasHitVertical) ? (int)ray.wallHitY % TILE_SIZE : (int)ray.wallHitX % TILE_SIZE;
    while (start < end)
    {
        dist_from_top = start + (wallstripheight/ 2) - (game_data.resolution_y / 2);
        offset_y = (int)(dist_from_top * (float)TILE_SIZE / wallstripheight);
        color = ptr.data[offset_y * TILE_SIZE + offset_x];
        my_mlx_pixel_put(&img, col, start, color);
        start++;
    }
}

void		ft_empty_trash(float rayangle, int col)
{
	float	distanceprojplane;
	float	raydist;
	float	an;
	float	wallstripheight;
	float	offset;

	an = rayangle - ray.rayAngle;
	raydist = ray.distance * cos(an);
	distanceprojplane = (game_data.resolution_y/ 2) / tan(FOV_ANGLE / 2);
	wallstripheight = (TILE_SIZE / raydist) * distanceprojplane;
	offset = ((ray.wasHitVertical == 0) ?
	fmod(ray.wallHitX, TILE_SIZE) : fmod(ray.wallHitY, TILE_SIZE));
	if (ray.isRayFacingDown && !ray.wasHitVertical)
		ft_draw_texture(g_west, col, offset, wallstripheight);
	else if (ray.isRayFacingLeft && ray.wasHitVertical)
		ft_draw_texture(g_east, col, offset, wallstripheight);
	else if (ray.isRayFacingRight && ray.wasHitVertical)
		ft_draw_texture(g_south, col, offset, wallstripheight);
	else if (ray.isRayFacingUp && !ray.wasHitVertical)
		ft_draw_texture(g_north, col, offset, wallstripheight);
}

void		get_text_data(void)
{
	g_north.ptr = mlx_xpm_file_to_image(mlx, game_data.no_txt,
			&g_north.width, &g_north.height);
	g_west.ptr = mlx_xpm_file_to_image(mlx, game_data.we_txt,
			&g_west.width, &g_west.height);
	g_south.ptr = mlx_xpm_file_to_image(mlx, game_data.so_txt,
			&g_south.width, &g_south.height);
	g_east.ptr = mlx_xpm_file_to_image(mlx, game_data.ea_txt,
			&g_east.width, &g_east.height);
	g_sprite.ptr = mlx_xpm_file_to_image(mlx, game_data.s_txt,
			&g_sprite.width, &g_sprite.height);
}

void		init_textures(void)
{
	get_text_data();
	if (g_north.ptr && g_west.ptr && g_south.ptr && g_east.ptr && g_sprite.ptr)
	{
		g_north.data = (int *)mlx_get_data_addr(g_north.ptr,
		&g_north.bits_per_pixel,
				&g_north.size_line, &g_north.endian);
		g_west.data = (int *)mlx_get_data_addr(g_west.ptr,
		&g_west.bits_per_pixel,
				&g_west.size_line, &g_west.endian);
		g_south.data = (int *)mlx_get_data_addr(g_south.ptr,
		&g_south.bits_per_pixel,
				&g_south.size_line, &g_south.endian);
		g_east.data = (int *)mlx_get_data_addr(g_east.ptr,
		&g_east.bits_per_pixel,
				&g_east.size_line, &g_east.endian);
		g_sprite.data = (int *)mlx_get_data_addr(g_sprite.ptr,
		&g_sprite.bits_per_pixel,
				&g_sprite.size_line, &g_sprite.endian);
	}
	
}

unsigned int		shadow(unsigned int color, int col)
{
	t_color			shadow;
	float			fact;
	unsigned int	dark;

	fact = 200 / g_ray_distance[col];
	shadow.r = (((color >> 16) & 0xFF)) * fact;
	shadow.g = (((color >> 8) & 0xFF)) * fact;
	shadow.b = ((color) & (0xFF)) * fact;
	dark = rgb_to_int(shadow.r, shadow.g, shadow.b);
	if (dark > color)
		dark = color;
	return (dark);
}

unsigned int	rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
	int c;

	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}