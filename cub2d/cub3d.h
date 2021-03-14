/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:53:17 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/14 17:36:58 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "utils/utils.h"
# include <stdio.h>
# include "get_next_line/get_next_line.h"
# include <math.h>
#include <stdbool.h>
# include <limits.h>
# define EXIT_KEY		53
# define KEY_RIGHT		124
# define KEY_LEFT		123
# define KEY_DOWN		125
# define KEY_UP			126
# define TILE_SIZE      64
# define PI 3.14
# define FOV_ANGLE (60 * (PI / 180))


#define MINI 0.3

int		*dst;
typedef struct player
{
    int x;
    int y;
}               t_player;

t_player player;

typedef struct			s_image
{
	int					width;
	int					height;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	void				*ptr;
	int					*data;
}						t_image;

typedef struct s_ray
{
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float  distance;
    float wasHitVertical;
    float isRayFacingDown;
    float isRayFacingUp;
    float isRayFacingLeft;
    float isRayFacingRight;
}               t_ray;

typedef struct s_player
{
    float rotationangle;
    float turndirection;
    float rotationspeed;
    float walkdirection;
    float movespeed;
    float movestep;
    float x;
    float y;
    float newplayerx;
    float newplayery;
    float dirangle;
}               t_plr;

t_plr nassim;

t_ray   ray;

typedef struct  s_cub {
    int           resolution_x;
    int         resolution_y;
    char*       no_path;
    char*       no_txt;
    char*       so_path;
    char*       so_txt;
    char*       we_path;
    char*       we_txt;
    char*       ea_path;
    char*       ea_txt;
    char*       s_path;
    char*       s_txt;  
     int     big_line;
int     big_colon;
}               t_cub;

typedef struct  s_color {
    char*       flor_a;
    char*       flor_b;
    int         color_x;
    int         color_y;
    int         color_z;
    int         color_xc;
    int         color_yc;
    int         color_zc;
    int         r;
    int         g;
    int         b;
}               t_color;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int					nb_of_sprites;
}               t_data;
typedef struct			s_sprites
{
	float				x;
	float				y;
	float				distance;
}						t_sprites;

typedef struct			s_datas
{
	int					width;
	int					height;
	t_color				floor;
	t_color				c;
	char				*map[50];
	int					cols;
	int					index;
	int					nb_of_rows;
	int					nb_of_cols;
	int					nb_of_sprites;
}						t_datas;

t_datas					g_data;
t_sprites				g_s_data[50];
t_image					g_north;
t_image					g_west;
t_image					g_south;
t_image					g_east;
t_image					g_sprite;
t_image					g_image;
char       **map;
char        **updated_map;
t_data  img;
float					g_ray_distance[2561];
float distanceBetweenPoints(float x1,float y1, float x2, float  y2);
t_cub   game_data;
t_color color;
void    *mlx;
void    *mlx_win;
void    ft_readmap(void);
void    ft_draw_sprites(void);
void			init_sprites(void);
char **fill_map();
void free_array(char **tab);
void        ft_draw_texture(t_image ptr, int col, float offset, float wallstripheight);
void		ft_empty_trash(float rayangle, int col);
void		get_text_data(void);
void		init_textures(void);
unsigned int		shadow(unsigned int color, int col);
unsigned int	rgb_to_int(unsigned int r, unsigned int g, unsigned int b);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif