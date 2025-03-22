#include "ft_strings.h"
#include <stdbool.h>

bool	is_element(char *line, const char *elem)
{
	int	keyword_len;

	keyword_len = ft_strcspn(line, " ");
	if (keyword_len == 0)
		return (false);
	return (ft_strncmp(line, elem, keyword_len) == 0);
}
