/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 01:13:27 by yademirk          #+#    #+#             */
/*   Updated: 2026/09/26 01:29:17 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_node* root;
	int	res;

	if (argc != 2)
	{
		printf("One arg, please.\n");
		return (1);
	}
	if (argv[1][0] == '\0')
		return (0);
	res = 0;
	root = parse_expression(argv[1]);
	if (root != NULL && root->error == ERR_NONE)
		printf("Result: %i\n", execute_node(root));
	else
		res = 1;
	destroy_tree(root);
	return (res);
}
