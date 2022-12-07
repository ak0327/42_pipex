/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:26:46 by takira            #+#    #+#             */
/*   Updated: 2022/12/06 19:26:47 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

// argv = {"  file1",
//		 "cmd1-1", " ", "", "cmd1-2",
//		 "cmd2-1", "cmd2-2 ", "  cmd2-3",
//		 " file2  "};
// cmd1 = {"cmd1-1", "cmd1-2", NULL};
// cmd2 = {"cmd2-1", "cmd2-2", "cmd2-3", NULL};
// infile = file1;
// outfile = file2;

int	main(int argc, char **argv)
{
	char	**input_chars;
	char	**cmd1;
	char	**cmd2;

	if (argc == 1)
		return (1);
	return (0);
}
