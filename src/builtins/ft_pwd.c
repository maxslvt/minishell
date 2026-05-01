#include "minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	if (cmd->cmd[1])
	{
		if (cmd->cmd[1][0] == '-' && cmd->cmd[1][1])
		{
			ft_putstr_fd("minishell: pwd: -%c: invalid option\n", cmd->cmd[1][1]);
			return (2);
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}