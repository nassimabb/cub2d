/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:25:25 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/18 14:27:38 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ray_direction(float angle)
{
    ray.rayAngle = normalizeAngle(angle);
    ray.wallHitX = 0;
    ray.wallHitY = 0;
    ray.distance = 0;
    ray.wasHitVertical = false;

    ray.isRayFacingDown = ray.rayAngle > 0 && ray.rayAngle < M_PI;
    ray.isRayFacingUp = !ray.isRayFacingDown;

    ray.isRayFacingRight = ray.rayAngle < (0.5 * M_PI) || ray.rayAngle > (1.5 * M_PI);
    ray.isRayFacingLeft = !ray.isRayFacingRight;
}


void    cast_ray(int col, float angle)
{
    ray_direction(angle);
    float xintercept, yintercept;
    float xstep, ystep;

     
    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    float foundHorzWallHit = false;
    float horzWallHitX = 0;
    float horzWallHitY = 0;

    // Find the y-coordinate of the closest horizontal grid intersenction
    yintercept = floor(nassim.y / TILE_SIZE) * TILE_SIZE;
    yintercept += ray.isRayFacingDown ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = nassim.x + (yintercept - nassim.y) / tan(ray.rayAngle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= ray.isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(ray.rayAngle);
    xstep *= (ray.isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (ray.isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX < game_data.big_colon * TILE_SIZE && nextHorzTouchY >= 0 && nextHorzTouchY < game_data.big_line * TILE_SIZE)
    {
        if (hasWallAt(nextHorzTouchX, nextHorzTouchY + (ray.isRayFacingUp ? -1 : 0)))
        {
            foundHorzWallHit = true;
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    ray_direction(angle);
    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    float foundVertWallHit = false;
    float vertWallHitX = 0;
    float vertWallHitY = 0;

    // Find the x-coordinate of the closest vertical grid intersenction
    xintercept = floor(nassim.x / TILE_SIZE) * TILE_SIZE;
    xintercept += ray.isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    yintercept = nassim.y + (xintercept - nassim.x) * tan(ray.rayAngle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= ray.isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(ray.rayAngle);
    ystep *= (ray.isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (ray.isRayFacingDown && ystep < 0) ? -1 : 1;
    

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX < game_data.big_colon * TILE_SIZE && nextVertTouchY >= 0 && nextVertTouchY < game_data.big_line * TILE_SIZE)
    {
        if (hasWallAt(nextVertTouchX  - (ray.isRayFacingLeft ? 1 : 0), nextVertTouchY))
        {
            foundVertWallHit = true;
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            break;
        }
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical distances and choose the smallest value
    float horzHitDistance = (foundHorzWallHit)
        ? distanceBetweenPoints(nassim.x, nassim.y, horzWallHitX, horzWallHitY)
        : INT_MAX;
    float vertHitDistance = (foundVertWallHit)
        ? distanceBetweenPoints(nassim.x, nassim.y, vertWallHitX, vertWallHitY)
        : INT_MAX;
    // printf("%.2f %.2f %.2f %.2f %.2f\n", xstep, ystep, horzHitDistance, vertHitDistance, ray.isRayFacingRight);

    // only store the smallest of the distances
    ray.wallHitX = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
    ray.wallHitY = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
    ray.distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
    ray.wasHitVertical = (vertHitDistance < horzHitDistance);
   
    ray.distance *= cos(nassim.dirangle - ray.rayAngle);
    g_ray_distance[col] = ray.distance; 
    //printf("0%f\n",ray.rayAngle);
    //printf("1%f\n",nassim.rotationangle);
    //ray.distance *= cos(ray.rayAngle);
    float perpDistance = ray.distance;
    float distanceProjPlane = (game_data.resolution_y / 2) / tan(FOV_ANGLE / 2);
    float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

    int wallStripHeight = projectedWallHeight;
    int wallTopPixel = (game_data.resolution_y / 2) - (wallStripHeight / 2);
    wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

    int wallBottomPixel = (game_data.resolution_y / 2) + (wallStripHeight / 2);
    wallBottomPixel = wallBottomPixel > game_data.resolution_y ? game_data.resolution_y : wallBottomPixel;
   
    colorr = rgb_to_int(color.color_x,color.color_y,color.color_z);

   // floor
    dda(game_data.resolution_y/2 + wallStripHeight/2, col,game_data.resolution_y, col);
    
    // sma  
   colorr = rgb_to_int(color.color_xc,color.color_yc,color.color_zc);
    dda( 0, col ,game_data.resolution_y/2 - wallStripHeight/2  ,col);

   ft_empty_trash(angle, col);
    //dda(nassim.x* MINI , nassim.y*MINI, ray.wallHitX*MINI, ray.wallHitY*MINI);
    
   // dda(col , 0, ray.wallHitX, ray.wallHitY);
    // CEILLINGd
    //ft_draw_line(col , 0, WINDOW_HEIGHT/2 - wallStripHeight/2);
    //dda(col , WINDOW_HEIGHT/2 - wallStripHeight/2, 0, WINDOW_HEIGHT/2 + wallStripHeight/2);
    // FLOOR
    //ft_draw_line(col , data.Height/2 + wallStripHeight/2, col, data.Height);

}