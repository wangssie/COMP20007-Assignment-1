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

// This function must read in a ski slope map and determine whether or not
// it is possible for the park ranger to trim all of the trees on the ski slope
// in a single run starting from the top of the mountain.
//
// The ski slope map is provided via stdin in the following format:
//
//   n m
//   from to
//   from to
//   ...
//   from to
//
// Here n denotes the number of trees that need trimming, which are labelled
// {1, ..., n}. The integer m denotes the number "reachable pairs" of trees.
// There are exactly m lines which follow, each containing a (from, to) pair
// which indicates that tree `to` is directly reachable from tree `from`.
// `from` and `to` are integers in the range {0, ..., n}, where {1, ..., n}
// denote the trees and 0 denotes the top of the mountain.
//
// For example the following input represents a ski slope with 3 trees and
// 4 reachable pairs of trees.
//
// input:            map:          0
//   3 4                          / \
//   0 1                         /  2
//   0 2                        / /
//   2 1                        1
//   1 3                          \
//                                 3
//
// In this example your program should return `true` as there is a way to trim
// all trees in a single run. This run is (0, 2, 1, 3).
//
// Your function should must:
//  - Read in this data from stdin
//  - Store this data in an appropriate data structure
//  - Run the algorithm you have designed to solve this problem
//  - Do any clean up required (e.g., free allocated memory)
//  - Return `true` or `false` (included in the stdbool.h library)
//
// For full marks your algorithm must run in O(n + m) time.


bool is_single_run_possible() {

  // read in data from stdin
  int n, m;
  scanf("%d %d\n", &n, &m);
  // add the 0 node
  n++;
  // create our adjacency list, adjacency count list and vertex node count list
  Vertex **adj_list = create_adjacency_list(n);
  int *adj_count_list = create_n_length_list(n);
  int *node_count_list = create_n_length_list(n);

  // initialise arrays so elements = -1
  initialise_array_to_x(adj_count_list, n, 0);
  initialise_array_to_x(node_count_list, n, 0);

  // store data in list
  Vertex node, adj_node;
  int adj_count;
  for (int i=0; i<m; i++) {
    // read in current node -> adj node
    scanf("%d %d\n", &node, &adj_node);
    // check how many nodes the current node is adjacent to so far
    adj_count = *(adj_count_list+node);
    // add adj node to the current node's adjacency list
    *(*(adj_list+node)+adj_count) = adj_node;
    // update current node's adjacency count by 1
    *(adj_count_list+node)+=1;
  }

  // update the max amount of nodes that precede a node
  update_node_count_list(adj_list, adj_count_list, node_count_list);

  // free allocated memory
  free_adjacency_list(adj_list, n);
  free(adj_count_list);

  // check if the node count of any node is n-1
  for (int i=0; i<n; i++) {
    if (*(node_count_list+i)== n-1) {
      free(node_count_list);
      return true;
    }
  }

  free(node_count_list);
  return false;
}

Vertex **create_adjacency_list(int n) {
  Vertex **array = (Vertex**)malloc(sizeof(Vertex*)*n);
  assert(array);
  for (int i=0; i<n; i++) {
    Vertex *subarray = (Vertex*)malloc(sizeof(Vertex)*(n-1));
    assert(subarray);
    *(array+i)=subarray;
  }
  return array;
}

int *create_n_length_list(int n) {
  int *array = (int*)malloc(sizeof(int)*n);
  assert(array);
  return array;
}

void initialise_array_to_x(int *array, int length, int x) {
  for (int i=0; i<length; i++) {
    *(array+i) = x;
  }
}

void update_node_count_list(Vertex **adj_list, int *adj_count_list, int *node_count_list) {
  // create queue
  Deque *queue = new_deque();
  // insert mountain node in the queue
  deque_insert(queue, MOUNTAIN_NODE);

  Vertex curr_node, adj_node;
  int curr_node_count, adj_node_count;

  // while the queue is empty
  while (!is_empty(queue)) {
    // pop the first node from queue and make it our current node
    curr_node = deque_pop(queue);
    curr_node_count = *(node_count_list+curr_node);
    // for each of the current node's adjacent nodes
    for (int i=0; i< *(adj_count_list+curr_node); i++) {
      adj_node = *(*(adj_list+curr_node)+i);
      adj_node_count = *(node_count_list+adj_node);

      // make adjacent node's node count the max between
      // itself OR
      // current node's node count + 1
      if (adj_node_count < curr_node_count+1) {
        *(node_count_list+adj_node)=curr_node_count+1;
        // add adjacent node to queue if not in queue already
        if (!contain_in_deque(queue, adj_node)) {
          deque_insert(queue, (Data)adj_node);
        }
      }
    }
  }
  // free queue
  free_deque(queue);
}

void print_adj_list(Vertex **adj_list, int *adj_count, int n) {
  int count;
  for (int i=0; i<n; i++) {
    count = *(adj_count+i);
    printf("node %d is adjacent to: ", i);
    for (int j=0; j<count; j++) {
      printf("%d ", *(*(adj_list+i)+j));
    }
    printf("\n");
  }
}

void print_list(int *list, int n) {
  printf("[ ");
  for (int i=0; i<n; i++) {
    printf("%d ", *(list+i));
  }
  printf("]\n");
}

void free_adjacency_list(Vertex **adj_list, int n) {
  // free all the subarrays
  for (int i=0; i<n; i++) {
    free(*(adj_list+i));
  }
  free(adj_list);
}


// TODO: Add any additional functions or types required to solve this problem.

// creates a structure for the new graph
