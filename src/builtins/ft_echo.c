#include "minishell.h"

static int	valid_flag(char *arg)
{
	int	j;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 2;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

static int	check_n(char **argv, int *start_index)
{
	int	i;
	int	is_option;

	is_option = 0;
	i = 1;
	while (argv[i] && valid_flag(argv[i]))
	{
		is_option = 1;
		*start_index = i + 1;
		i++;
	}
	return (is_option);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->cmd[1])
	{
		if (check_n(cmd->cmd, &i))
			newline = 0;
		while (cmd->cmd[i])
		{
			write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
			if (cmd->cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}