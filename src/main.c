#include "minishell.h"

static t_cmd	*parse_line(char *line, t_var *env, int status, int *err)
{
	t_token	*tokens;
	t_cmd	*commands;

	(void)env;
	if (err)
		*err = 0;
	if (!line || line[0] == '\0')
		return (NULL);
	tokens = tokenize_line(line);
	if (!tokens)
	{
		if (err)
			*err = 2;
		return (NULL);
	}
	commands = parsing(tokens, env, status, err);
	free_token_list(tokens);
	if (!commands)
		return (NULL);
	return (commands);
}

static int	process_line(char *line, t_var **env, int status)
{
	t_cmd	*cmd_list;
	int		error_code;

	if (line[0] == '\0')
		return (status);
	error_code = 0;
	cmd_list = parse_line(line, *env, status, &error_code);
	if (!cmd_list)
	{
		if (error_code != 0)
			return (error_code);
		return (0);
	}
	if (cmd_list)
	{
		if (process_heredocs(cmd_list, *env, status) == -1)
		{
			status = 130;
			g_sig = 0;
		}
		else
			status = execute_pipeline(cmd_list, env, status);
		ft_free_cmd_list(cmd_list);
	}
	return (status);
}

static int	shell_loop_iteration(t_var **env, int status)
{
	char	*line;
	int		fd;

	g_sig = 0;
	line = readline("minishell$ ");
	fd = open("/dev/tty", O_RDONLY);
	if (!line)
	{
		ft_putstr_fd("exit\n", fd);
		close(fd);
		return (-1);
	}
	if (g_sig == SIGINT && line[0] == '\0')
	{
		g_sig = 0;
		free(line);
		return (130);
	}
	g_sig = 0;
	if (line[0] != '\0')
	{
		add_history(line);
		status = process_line(line, env, status);
	}
	return (free(line), status);
}

int	main(int ac, char **av, char **envp)
{
	t_var	*env;
	int		status;
	int		last_status;

	(void)av;
	if (ac != 1)
	{
		printf("Utilisation: ./minishell\n");
		return (1);
	}
	env = create_env(envp);
	if (!env)
		return (ft_free_env(env), 0);
	setup_signal_handlers();
	status = 0;
	last_status = 0;
	while (status != -1)
	{
		last_status = status;
		status = shell_loop_iteration(&env, status);
	}
	rl_clear_history();
	ft_free_env(env);
	return (last_status);
}