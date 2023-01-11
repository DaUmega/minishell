/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 13:37:37 by pdong         #+#    #+#                 */
/*   Updated: 2023/01/11 14:53:17 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

t_pipe	*pipe_creator(int n)
{
	t_pipe	*ans;
	t_pipe	*temp;
	int		i;

	i = 0;
	ans = NULL;
	while (i < n)
	{
		temp = ft_lnew(i);
		ft_ladd_end(&ans, temp);
		i++;
	}
	return (ans);
}

void	close_all_fd(t_pipe **pipes)
{
	t_pipe	*temp;

	temp = *pipes;
	while (temp)
	{
		close(temp->fd[1]);
		close(temp->fd[0]);
		temp = temp->next;
	}
}

void	child(t_pipe *temp)
{
	int		n;

	if (read(temp->fd[0], &n, sizeof(int)) < 0)
		ft_error("read");
	n = n + 5;
	if (!temp->next)
		ft_printf("%d\n", n);
	else if (write(temp->next->fd[1], &n, sizeof(int)) < 0)
		ft_error("write");
}

void	pipe_ft(t_pipe **pipes)
{
	t_pipe	*temp;
	pid_t	pid;

	temp = *pipes;
	while (temp)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork");
		if (pid == 0)
		{
			child(temp);
			close_all_fd(pipes);
			break ;
		}
		else
			waitpid(pid, NULL, 0);
		temp = temp->next;
	}
}

int	main(void)
{
	t_pipe	*temp;
	int		i;

	i = 0;
	temp = pipe_creator(1000);
	if (write(temp->fd[1], &i, sizeof(int)) < 0)
		ft_error("write");
	pipe_ft(&temp);
	close_all_fd(&temp);
	exit(EXIT_SUCCESS);
}
