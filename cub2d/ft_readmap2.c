/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readmap2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:32:56 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/19 18:03:34 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int i;
	int len;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}


void    split_tab(char *line)
{
	char **tab = ft_split(line ,' ');
	if (ft_tablen(tab))
	{
		if (!ft_strncmp(tab[0],"R",1))
			ressolution(&game_data.resolution_x, &game_data.resolution_y, tab);
		else if (!ft_strncmp(tab[0],"NO",2))
			save_path(&game_data.no_path, &game_data.no_txt, tab);
		else if (!ft_strncmp(tab[0],"SO",2))
			save_path(&game_data.so_path, &game_data.so_txt, tab);
		else if (!ft_strncmp(tab[0],"WE",2))
			save_path(&game_data.we_path, &game_data.we_txt, tab);
		else if (!ft_strncmp(tab[0],"EA",2))
			save_path(&game_data.ea_path, &game_data.ea_txt, tab);
		else if (!ft_strncmp(tab[0],"S",2))
			save_path(&game_data.s_path, &game_data.s_txt, tab);
		else if (!ft_strncmp(tab[0],"F",1))
			save_color(line, tab, &color.flor_a);
		else if (!ft_strncmp(tab[0],"C",1))
			save_color(line, tab, &color.flor_b);
		else if (ft_isdigit(*line) || *line == ' ')
			map = ft_realloc(map, line);
	}
	free_tab(tab);
	
}

void    ressolution(int* x , int* y, char **tab)
{

	if (ft_tablen(tab) != 3)
		exit_game(cub, 23);
	int i;
	int len = ft_strlen(tab[1]);
	i = -1;
	while (++i < len)
		if (!ft_isdigit(tab[1][i]))
			exit_game(cub, 23);
	i = -1;
	len = ft_strlen(tab[2]);
	while (++i < len)
		if (!ft_isdigit(tab[2][i]))
			exit_game(cub, 23);
	*x = ft_atoi(tab[1]);
	*y = ft_atoi(tab[2]);
		if (*x > 2561 )
			*x = 2560;
		if (*y > 1440)
			*y = 1440;
	//free_tab(tab);
}

void save_path(char **path, char **text, char **tab)
{
	*path = ft_strdup(tab[0]);
    *text = ft_strdup(tab[1]);
	//free_tab(tab);
}

void save_color(char *line, char **tab, char **color_floor)
{
	if (!ft_strncmp(tab[0],"F",1))
    	ft_split2(tab[1]);
	else if (!ft_strncmp(tab[0],"C",1))
		ft_splitc(tab[1]);
	//free_tab(tab);
}
