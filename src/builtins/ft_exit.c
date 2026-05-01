#include "minishell.h"

static int	is_numeric_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
}

static int	check_overflow(char *str)
{
	unsigned long long	res;
	int					sign;
	int					i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (res > 922337203685477580ULL || (res == 922337203685477580ULL
				&& ((sign == 1 && str[i] - '0' > 7)
					|| (sign == -1 && str[i] - '0' > 8))))
			return (1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (0);
}

int	ft_exit(t_cmd *cmd, t_var **env, int last_status)
{
	int	fd_tty;
	int	i;

	fd_tty = open("/dev/tty", O_RDWR);
	if (fd_tty)
	{
		ft_putstr_fd("exit\n", fd_tty);
		close(fd_tty);
	}
	if (!cmd->cmd[1])
		ft_free_exit(cmd, env, last_status);
	if (!is_numeric_str(cmd->cmd[1]) || check_overflow(cmd->cmd[1]))
	{
		exit_error(cmd->cmd[1], ": numeric argument required\n");
		ft_free_exit(cmd, env, 2);
	}
	if (cmd->cmd[2])
	{
		exit_error(NULL, "too many arguments\n");
		ft_free_exit(cmd, env, 1);
	}
	i = ft_atoi(cmd->cmd[1]) % 256;
	ft_free_exit(cmd, env, i);
	return (i);
}