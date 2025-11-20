#include "../mlx/mlx.h"
#include "../libft/libft.h"

typedef struct s_map {
	char	**map;
	int		width;
	int		height;
	int		coin_total;
	int		coin_count;
	int		exit_count;
	int		player_count;
} t_map ;
