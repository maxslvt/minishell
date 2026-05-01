#include "minishell.h"

int	err_msg(const char *pfx, const char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (pfx)
	{
		ft_putstr_fd((char *)pfx, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (code);
}