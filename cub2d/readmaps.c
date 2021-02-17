/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:49:14 by nabboudi          #+#    #+#             */
/*   Updated: 2021/02/11 18:02:03 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void       ft_split2(char* tab)
{
    char **tab2;
    char* num;
    num = tab;
    tab2 = ft_split(num ,',');
    color.color_x = ft_atoi(tab2[0]);
    color.color_y = ft_atoi(tab2[1]);
    color.color_z = ft_atoi(tab2[2]);
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
    ret[i] = ft_strdup(element);
    ret[i + 1] = NULL;
    return (ret);
}

void       ft_readmap(void)
{
    char *line;
    char **tab;
    int fd;


    map = NULL;                                                                                               
    fd = open("map.cub",O_RDONLY);
    while (get_next_line(fd,&line))
    {
        tab = ft_split(line ,' ');
        if(ft_tablen(tab))
        {
            //(ft_strlen(tab[0]) > 1 ? ft_strlen(tab[0]) : 1))
            if (!ft_strncmp(tab[0],"R",1))
            {   // check if tab[1] and tab[2] all num
                game_data.resolution_x = ft_atoi(tab[1]);
                game_data.resolution_y = ft_atoi(tab[2]);
            }
            else if (!ft_strncmp(tab[0],"NO",2))
            {
                game_data.no_path = tab[0];
                game_data.no_txt = tab[1];
            }
            else if (!ft_strncmp(tab[0],"SO",2))
            {
                game_data.so_path = tab[0];
                game_data.so_txt = tab[1];
            }
            else if (!ft_strncmp(tab[0],"WE",2))
            {
                game_data.we_path = tab[0];
                game_data.we_txt = tab[1];
            }
            else if (!ft_strncmp(tab[0],"EA",2))
            {
                game_data.ea_path = tab[0];
                game_data.ea_txt = tab[1];
            }
            else if (!ft_strncmp(tab[0],"S",2))
            {
                game_data.s_path = tab[0];
                game_data.s_txt= tab[1];
            }
            else if (!ft_strncmp(tab[0],"F",1))
            {
                tab = ft_split(line ,' ');
                color.flor_a = tab[0];
                ft_split2(tab[1]);
            }
            else if (!ft_strncmp(tab[0],"C",1))
            {
                tab = ft_split(line ,' ');
                color.flor_b = tab[0];
                ft_splitc(tab[1]);
            }
            else if (ft_isdigit(*line) || *line == ' ' || *line == '\t')
                map = ft_realloc(map, line);
        }
    }
    int i;

	i = -1;
	while (++i < ft_tablen(map))
		printf("%s\n", map[i]);
   // printf("%d\n",color.color_xc );
   // printf("%d\n",color.color_yc );
   // printf("%d\n",color.color_zc);
}
