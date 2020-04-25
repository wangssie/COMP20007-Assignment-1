/* * * * * * *
 * Park Ranger module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#ifndef PARKRANGER_H
#define PARKRANGER_H

#include <stdbool.h>
#include "deque.h"
#include "util.h"


typedef int Tree;

// Checks if a single run can go pass all the trees
bool is_single_run_possible();

// Create an adjacency list using a 2D Tree array
// array[i] = an array of all the adjacent trees of node i
// x adjacent to y meaning x -> y (directional adjacency)
Tree **create_adjacency_list(int n);

// Create an array of length n
int *create_n_length_list(int n);

// Initialise all elements in array to int x
void initialise_array_to_x(int *array, int length, int x);

// Reads in stdin and updates the adjacency list and adjacency count list
void update_adjacency_list(Tree **adj_list, int *adj_count_list, int edge_count);

// Updates array "node_count_list"
// node_count_list[i] = the maximum amount of nodes that can be visisted
//                      before reaching node i
void update_node_count_list(Tree **adj_list, int *adj_count_list, int *node_count_list);

// Free the memory associated with an adjacency list
void free_adjacency_list(Tree **adj_list, int n);

// Print out the adjacency list
// Format for each node (in newline): node x is adjacent to: x1 x2 ...
void print_adj_list(Tree **adj_list, int *adj_count, int n);

// Print out the elements of an array with length n
// Format: [ a1 a2 ... an ]
void print_list(int *list, int n);

#endif
