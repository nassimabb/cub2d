#!/bin/sh
#export MallocStackLogging=1  
gcc -g cub3d.c -lmlx -framework appkit -framework opengl   -D BUFFER_SIZE=1000 libft.a get_next_line/get_next_line.c get_next_line/get_next_line.h get_next_line/get_next_line_utils.c readmaps.c circle.c sprites.c cub3d.h ft_readmap2.c && ./a.out
