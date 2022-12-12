/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:40:09 by takira            #+#    #+#             */
/*   Updated: 2022/12/12 18:40:11 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

// ./pipex  infile    cmd1     cmd2  ...   cmdn     outfile
// -> argc >= 5

int multi_pipe_controller(int argc, char **argv)
{
	t_pipe	p;
	int		exit_status;

	printf("## multi_pipe ##\n");
	//init
	init_pipe_params_b(&p, &argv, argc - 3, NULL);

	//get input
	get_env_paths_b(&p, EXIT_FAILURE);
	get_input_cmds(&p, EXIT_FAILURE);
	get_file_names_b(&p, EXIT_FAILURE);

	// do pipes && update exit_status
//	exit_status = multi_pipe();
	exit_status = 0;

	// frees
//	free_allocs_b(&p);


	// return(exit_status);
//	init_pipe_params_b(&p, &argv);
//	init_cmd_params_b(&p);
//	get_inputs_b(&p, EXIT_FAILURE);
//	exit_status = exec_pipe_b(&p, EXIT_FAILURE);
//	free_allocs_b(&p);
	return (exit_status);
}
