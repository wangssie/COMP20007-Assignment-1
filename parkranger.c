/* * * * * * *
 * Park Ranger module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parkranger.h"
#include "util.h"
#include "deque.h"

#define MOUNTAIN_NODE 0

bool is_single_run_possible() {

  // read in our number of trees (n) and number of edges (m)
  int n, m;
  scanf("%d %d\n", &n, &m);
  // add the 0/mountain node to our Tree count
  n++;

  // create our adjacency list, adjacency count list and Tree node count list
  Tree **adj_list = create_adjacency_list(n);
  int *adj_count_list = create_n_length_list(n);
  int *node_count_list = create_n_length_list(n);

  // initialise arrays so elements = 0
  initialise_array_to_x(adj_count_list, n, 0);
  initialise_array_to_x(node_count_list, n, 0);

  // store adjacency list info from stdin into adj_list
  update_adjacency_list(adj_list, adj_count_list, m);

  // calculate the max number of you nodes can pass before reaching a node
  // store result in node_count_list
  update_node_count_list(adj_list, adj_count_list, node_count_list);

  // free allocated memory
  free_adjacency_list(adj_list, n);
  free(adj_count_list);

  // check if any node was able to pass every other node before reaching it
  // AKA node_count = n-1
  int i=0;
  for (i; i<n; i++) {
    // if yes: the trees can be trimmed in one run
    if (*(node_count_list+i)== n-1) {
      free(node_count_list);
      return true;
    }
  }
  // if no: no single path goes passed all nodes
  // the trees cannot be trimmed in one run
  free(node_count_list);
  return false;
}

// Create an adjacency list using a 2D Tree array
// array[i] = an array of all the adjacent trees of node i
// x adjacent to y meaning x -> y (directional adjacency)
Tree **create_adjacency_list(int n) {
  Tree **array = (Tree**)malloc(sizeof(Tree*)*n);
  assert(array);
  int i=0;
  for (i; i<n; i++) {
    Tree *subarray = (Tree*)malloc(sizeof(Tree)*(n-1));
    assert(subarray);
    *(array+i)=subarray;
  }
  return array;
}

// Create an array of length n
int *create_n_length_list(int n) {
  int *array = (int*)malloc(sizeof(int)*n);
  assert(array);
  return array;
}

// Initialise all elements in array to int x
void initialise_array_to_x(int *array, int length, int x) {
  int i=0;
  for (i; i<length; i++) {
    *(array+i) = x;
  }
}


// Reads in stdin and updates the adjacency list and adjacency count list
void update_adjacency_list(Tree **adj_list, int *adj_count_list, int edge_count) {
  Tree node, adj_node;
  int adj_count;
  int i=0;
  for (i; i<edge_count; i++) {
    // read in current node -> adj node
    scanf("%d %d\n", &node, &adj_node);
    // check how many nodes the current node is adjacent to so far
    adj_count = *(adj_count_list+node);
    // add adj node to the current node's adjacency list
    *(*(adj_list+node)+adj_count) = adj_node;
    // update current node's adjacency count by 1
    *(adj_count_list+node)+=1;
  }
}

// Updates array "node_count_list"
// node_count_list[i] = the maximum amount of nodes that can be visisted
//                      before reaching node i
void update_node_count_list(Tree **adj_list, int *adj_count_list, int *node_count_list) {
  // create queue
  Deque *queue = new_deque();
  // insert mountain node in the queue
  deque_insert(queue, MOUNTAIN_NODE);

  Tree curr_node, adj_node;
  int curr_node_count, adj_node_count;

  // while the queue is empty
  while (!is_empty(queue)) {
    // pop the first node from queue and make it our current node
    curr_node = deque_pop(queue);
    curr_node_count = *(node_count_list+curr_node);
    // for each of the current node's adjacent nodes
    int i=0;
    for (i; i< *(adj_count_list+curr_node); i++) {
      adj_node = *(*(adj_list+curr_node)+i);
      adj_node_count = *(node_count_list+adj_node);

      // make adjacent node's node count the max between
      // itself OR
      // current node's node count + 1
      if (adj_node_count < curr_node_count+1) {
        *(node_count_list+adj_node)=curr_node_count+1;
        // add adjacent node to queue if node count changed
        // AND it's not in the queue already
        if (!contain_in_deque(queue, adj_node)) {
          deque_insert(queue, (Data)adj_node);
        }
      }
    }
  }
  // free memory associated with queue
  free_deque(queue);
}

// Free the memory associated with an adjacency list
void free_adjacency_list(Tree **adj_list, int n) {
  // free all the subarrays
  int i=0;
  for (i; i<n; i++) {
    free(*(adj_list+i));
  }
  free(adj_list);
}

// Print out the adjacency list
// Format for each node (in newline): node x is adjacent to: x1 x2 ...
void print_adj_list(Tree **adj_list, int *adj_count, int n) {
  int count, i=0, j=0;
  for (i; i<n; i++) {
    count = *(adj_count+i);
    printf("node %d is adjacent to: ", i);
    j=0;
    for (j; j<count; j++) {
      printf("%d ", *(*(adj_list+i)+j));
    }
    printf("\n");
  }
}

// Print out the elements of an array with length n
// Format: [ a1 a2 ... an ]
void print_list(int *list, int n) {
  printf("[ ");
  int i=0;
  for (i; i<n; i++) {
    printf("%d ", *(list+i));
  }
  printf("]\n");
}



// TODO: Add any additional functions or types required to solve this problem.

// creates a structure for the new graph
