/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 13:37:37 by pdong         #+#    #+#                 */
/*   Updated: 2023/01/10 19:49:40 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

t_pipe	*pipe_creator(int n)
{
	t_pipe	*pipes;
	t_pipe	*temp;
	int		i;

	i = 0;
	pipes = NULL;
	while (i < n)
	{
		temp = ft_lnew(i);
		ft_ladd_end(&pipes, temp);
		i++;
	}
	return (pipes);
}

void	pipe_ft(t_pipe **pipes, int fd[2])
{
	t_pipe	*temp;
	int		pid;
	int		n;

	temp = *pipes;
	while (temp)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork");
		ft_printf("reading from: %d\n", fd[0]);
		if (pid == 0)
		{
			if (read(fd[0], &n, sizeof(int)) < 0)
				ft_error("read");
			n = n + 5;
			close(fd[0]);
			if (!temp->next)
			{
				ft_printf("%d\n", n);
				exit(EXIT_SUCCESS);
			}
			ft_printf("writing to: %d\n", fd[1]);
			if (write(fd[1], &n, sizeof(int)) < 0)
				ft_error("write");
			close(fd[1]);
		}
		else
			waitpid(pid, NULL, 0);
		temp = temp->next;
	}
}

void	leakchk(void)
{
	system("leaks -q pipex");
}

int	main(void)
{
	t_pipe	*temp;
	int		fd[2];
	int		i;

	atexit(leakchk);
	i = 0;
	if (pipe(fd) < 0)
		ft_error("pipe");
	temp = pipe_creator(1);
	ft_printf("writing to: %d\n", fd[1]);
	if (write(fd[1], &i, sizeof(int)) < 0)
		ft_error("write");
	pipe_ft(&temp, fd);
	close(fd[0]);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}
