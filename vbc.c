/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 01:14:57 by yademirk          #+#    #+#             */
/*   Updated: 2026/09/26 01:30:42 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "vbc.h"

void destroy_tree(t_node* tree)
{
	if (!tree)
		return;
	destroy_tree(tree->left);
	destroy_tree(tree->right);
	free(tree);
}

t_node* new_node(int val, NODE_TYPE type, t_node* left, t_node* right)
{
	t_node* node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->val = val;
	node->type = type;
	node->left = left;
	node->right = right;
	node->error = ERR_NONE;
	return (node);
}

static t_node* parse_add(char *str, int *i);

static t_node* parse_paren(char *str, int *i)
{
	t_node	*left = NULL;

	if (str[*i] == '(')
	{
		*i += 1;
		left = parse_add(str, i);
		if (left == NULL || left->error != ERR_NONE)
			return (left);
		else if (str[*i] != ')')
			left->error = ERR_UNEXPECTED_TOKEN;
		else
			(*i)++;
	}
	else if (isdigit(str[*i]))
	{
		left = new_node(str[*i] - '0', TYPE_VAL, NULL, NULL);
		*i += 1;
	}
	else
	{
		left = new_node(0, TYPE_VAL, NULL, NULL);
		if (str[*i] == '\0')
			left->error = ERR_UNEXPECTED_EOF;
		else
			left->error = ERR_UNEXPECTED_TOKEN;
	}
	return (left);
}

static t_node* parse_mult(char *str, int *i)
{
	t_node	*left = NULL;
	t_node	*right = NULL;

	left = parse_paren(str, i);
	if (left == NULL || left->error != ERR_NONE)
		return left;
	while (str[*i] == '*')
	{
		*i += 1;
		right = parse_paren(str, i);
		if (right == NULL || right->error != ERR_NONE)
		{
			destroy_tree(left);
			return (right);
		}
		left = new_node(0, TYPE_MULT, left, right);
	}
	return (left);
}


static t_node* parse_add(char *str, int *i)
{
	t_node	*left = NULL;
	t_node	*right = NULL;

	left = parse_mult(str, i);
	if (left == NULL || left->error != ERR_NONE)
		return left;
	while (str[*i] == '+')
	{
		*i += 1;
		right = parse_mult(str, i);
		if (right == NULL || right->error != ERR_NONE)
		{
			destroy_tree(left);
			return (right);
		}
		left = new_node(0, TYPE_ADD, left, right);
	}
	return (left);
}

static void print_error(t_node *node, char error_char)
{
	if (node == NULL)
		printf("Unexpected error\n");
	else if (node->error == ERR_UNEXPECTED_TOKEN)
		printf("Unexpected token %c\n", error_char);
	else if (node->error == ERR_UNEXPECTED_EOF)
		printf("Unexpected end of input\n");
}

t_node* parse_expression(char *str)
{
	t_node* root;
	int	i = 0;

	root = parse_add(str, &i);
	if (str[i] != '\0' && root != NULL && root->error == ERR_NONE)
		root->error = ERR_UNEXPECTED_TOKEN;
	if (root == NULL || root->error != ERR_NONE)
		print_error(root, str[i]);
	return (root);
}

int execute_node(t_node* root)
{
	int	left = 0;
	int	right = 0;

	if (root->left == NULL && root->right == NULL)
		return (root->val);
	if (root->left != NULL)
		left = execute_node(root->left);
	if (root->right != NULL)
		right = execute_node(root->right);
	if (root->type == TYPE_MULT)
		return (left * right);
	else if (root->type == TYPE_ADD)
		return (left + right);
	else
		return (root->val);
}
