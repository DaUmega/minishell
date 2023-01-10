/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 16:03:38 by pdong         #+#    #+#                 */
/*   Updated: 2023/01/10 19:49:13 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipe
{
	int				index;
	struct s_pipe	*prev;
	struct s_pipe	*next;
}	t_pipe;

void	ft_error(char *s);
t_pipe	*ft_lnew(int index);
void	ft_ladd_end(t_pipe **lst, t_pipe *new);
int		lstsize(t_pipe **a);

void	ft_debug(t_pipe **lst);

#endif