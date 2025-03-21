#include "../inc/error.h"
#include "../libft/inc/libft.h"

/**
 * @brief Handles errors by printing appropriate error messages
 *
 * @param err_code The error code indicating the type of error
 * @param context Additional context for the error message
 */
void	handle_error(t_error err_code, char *context)
{
	if (err_code == ERR_INVALID_ARGS)
		ft_printf("Error: %s - Invalid arguments\n", context);
	else if (err_code == ERR_FILE_OPEN)
		ft_printf("Error: %s - Failed to open file\n", context);
	else if (err_code == ERR_MALLOC_FAIL)
		ft_printf("Error: %s - Memory allocation failed\n", context);
	else if (err_code == ERR_MAP_INVALID)
		ft_printf("Error: %s - Map validation failed\n", context);
	else if (err_code == ERR_MAP_WALLS)
		ft_printf("Error: %s - Map walls check failed\n", context);
	else if (err_code == ERR_MAP_RECTANGLE)
		ft_printf("Error: %s - Map is not a rectangle\n", context);
	else if (err_code == ERR_MAP_ENTITIES)
		ft_printf("Error: %s - Invalid count of entities\n", context);
	else
		ft_printf("Error: %s - Unknown error\n", context);
} 