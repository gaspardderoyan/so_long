#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/inc/libft.h"
# include "../inc/error.h"
# include <fcntl.h>
# include <stddef.h>
# include <sys/types.h>

enum Cell {
	EMPTY = 1,
	WALL,
	COIN,
	EXIT,
	START
};

typedef struct s_position {
	int	x;
	int	y;
} t_position;

typedef struct s_master {
	size_t		lines;
	size_t		len;
	u_int8_t	**map;
	t_position	*start;
	t_list		*char_map;
} t_master;

// MAP INPUT & FIRST CHECK //
// parse_map.c //
t_master	*init_master(void);
t_error		process_map(int	fd, t_master *master);

// convert_map.c //
u_int8_t	**convert_map(t_list *char_map, size_t lines, t_position *start);

// bfs.c //
t_error		bfs(u_int8_t **map, t_position *start);

// memory.c //
void		free_master(t_master *master);
void		free_map(u_int8_t **map, size_t lines);

// main.c //
void		print_map(u_int8_t **map, bool free_map);

#endif
