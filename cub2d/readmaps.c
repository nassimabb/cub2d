/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:49:14 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/17 11:54:56 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void free_array(char **tab)
{
    int i;

    i = -1;
    while (tab[++i])
        free(tab[i]);
    free(tab);
}

char **fill_map()
{
    char **tab;
    int i;
    int j;

    tab = malloc(sizeof(char*) * (game_data.big_colon + 1));
    i = 0;
    while (i < game_data.big_colon)
    {
        tab[i] = malloc(sizeof(char) * game_data.big_line + 1);
        j = 0;
        while (j < game_data.big_line)
        {
            if (j < ft_strlen(map[i]))
                tab[i][j] = map[i][j];
            else
                tab[i][j] = '1';
            j++;
        }
        tab[i][j] = '\0';
        free(map[i]);
        i++;
    }
    tab[i] = NULL;
    free(map);
    return tab;
}

void       ft_split2(char* tab)
{
    char **tab2;
    char* num;
    num = tab;
    tab2 = ft_split(num ,',');
    color.color_x = ft_atoi(tab2[0]);
    color.color_y = ft_atoi(tab2[1]);
    color.color_z = ft_atoi(tab2[2]);
    free_tab(tab2);
}

void       ft_splitc(char* tab)
{
    char **tab2;
    char* num;
    num = tab;
    tab2 = ft_split(num ,',');
    color.color_xc = ft_atoi(tab2[0]);
    color.color_yc = ft_atoi(tab2[1]);
    color.color_zc = ft_atoi(tab2[2]);
    free_tab(tab2);
}

void    ft_countmap(void)
{
    int     i;
    int     j;
        
    j = 0;    
    j = ft_tablen(map);
    i = 0;
    game_data.big_line = ft_strlen(map[i]);
    while (i < j - 1)
    {
        if (game_data.big_line < ft_strlen(map[i + 1]))
            game_data.big_line = ft_strlen(map[i + 1]);
        i++;
    }
    game_data.big_colon = j;
}

char    **ft_realloc(char **tab, char *element)
{
    int     i;
    char    **ret;
    int     len;

    i = 0;
    len = 1;
    if (tab)
        len = ft_tablen(tab) + 1;
    ret = (char **)malloc(sizeof(char *) * (len + 1));
    while (i < len - 1)
    {
        ret[i] = ft_strdup(tab[i]);
        i++;
    }
    free_tab(tab);
    ret[i] = ft_strdup(element);
    ret[i + 1] = NULL;
    game_data.big_colon += 1;
    if (game_data.big_line < ft_strlen(element))
        game_data.big_line = ft_strlen(element);
        
    return (ret);
}

void       ft_readmap(void)
{
    char *line;
    int fd;


    map = NULL;
    line = NULL;                                                                                         
    fd = open("map.cub",O_RDONLY);
    while (get_next_line(fd,&line) == 1)
    {
        split_tab(line);
        free(line);
    }
    free(line);
    close(fd);
}
