#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <stddef.h>
#include <sys/types.h>

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
	size_t	    len;
	u_int8_t	**map;
	t_position	*start;
	t_list		*char_map;
} t_master;

// MAP INPUT & FIRST CHECK //
// parse_map.c //
bool	process_map(int	fd, t_master *master);
