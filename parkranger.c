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
  // store data in list
  // free allocated memory
  // return true or false

  return false;
}

// TODO: Add any additional functions or types required to solve this problem.

// creates a structure for the new graph
graph_t *new_graph(void) {
  graph_t *graph = malloc(sizeof(*graph));
  assert(graph);
  int vertex_count, edge_count;
  scanf("%d %d\n", &vertex_count, &edge_count);
  graph->vertex_count = vertex_count;
  graph->edge_count = edge_count;
  return graph;
}

// creates an adjacency list
void add_vertices(graph_t *graph) {


}

void free_graph(graph_t *graph) {
  node_t *node;
  // free all the nodes vertices
  for (int i=0; i<graph->vertex_count; i++) {
      node = *(vertex_list+i);
      free_node(node);
  }
  // free the graph
  free(graph);
}

void free_node(node_t *node) {
  free(node->adj_list);
  free(node);
}
