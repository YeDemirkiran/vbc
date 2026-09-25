/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 01:14:38 by yademirk          #+#    #+#             */
/*   Updated: 2026/09/26 01:25:54 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBC_H
# define VBC_H

typedef enum
{
	TYPE_VAL,
	TYPE_MULT,
	TYPE_ADD,
} NODE_TYPE;

typedef enum
{
	ERR_NONE,
	ERR_UNEXPECTED_TOKEN,
	ERR_UNEXPECTED_EOF,
} NODE_ERROR;

typedef struct s_node t_node;

typedef struct s_node
{
	int	val;
	NODE_TYPE type;
	NODE_ERROR error;
	t_node *left;
	t_node *right;
}	t_node;

void	destroy_tree(t_node* tree);
t_node* new_node(int val, NODE_TYPE type, t_node* left, t_node* right);
t_node* parse_expression(char *str);
int		execute_node(t_node* root);

#endif
