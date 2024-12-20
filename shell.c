#include "shell.h"

/**
 * main - Entry point for the shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char **args = NULL;
	char *user_input = NULL;
	pid_t pid;

	while (1)
	{
		print_prompt();
		user_input = read_line();
		args = tokenize(user_input);
		exit_func(args, user_input);

		if (args[0] != NULL && strcmp(args[0], "env") != 0)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				if (execve(args[0], args, environ) == -1)
				{
					fprintf(stderr, "%s: command not found: %s\n", args[0], args[0]);
					exit(EXIT_FAILURE);
				}
			} else
			{
				int status;

				waitpid(pid, &status, 0);
			}
		}
		free(args);
	}
	free(user_input);
	return (0);
}
