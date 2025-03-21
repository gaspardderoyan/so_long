#ifndef ERROR_H
# define ERROR_H

typedef enum e_error {
	ERR_SUCCESS = 0,
	ERR_INVALID_ARGS,
	ERR_FILE_OPEN,
	ERR_MALLOC_FAIL,
	ERR_MAP_INVALID,
	ERR_MAP_WALLS,
	ERR_MAP_RECTANGLE,
	ERR_MAP_ENTITIES
} t_error;

void	handle_error(t_error err_code, char *context);

#endif 