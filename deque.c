/* * * * * * *
 * Deque module (i.e., double ended queue) for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

// You must not change any of the code already provided in this file, such as
// type definitions, constants or functions.
//
// You may, however, add additional functions and/or types which you may need
// while implementing your algorithms and data structures.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "deque.h"
#include "util.h"

// Create a new empty Deque and return a pointer to it
Deque *new_deque() {
	Deque *deque = malloc(sizeof(*deque));
	assert(deque);

	deque->top = NULL;
	deque->bottom = NULL;
	deque->size = 0;

	return deque;
}

// Free the memory associated with a Deque
void free_deque(Deque *deque) {
  // Remove (and thus free) all of the nodes in the Deque.
  while (deque->size > 0) {
    deque_remove(deque);
  }

	// Free the deque struct itself
	free(deque);
}

// Create a new Node with a given piece of data
Node *new_node(Data data) {
  Node *node = malloc(sizeof(*node));
  assert(node);

  node->next = NULL;
  node->prev = NULL;
  node->data = data;

  return node;
}

// Free the memory associated with a Node
void free_node(Node *node) {
  free(node);
}

// Add an element to the top of a Deque
void deque_push(Deque *deque, Data data) {
  Node *new = new_node(data);

  if (deque->size > 0) {
    new->next = deque->top;
    deque->top->prev = new;
  } else {
    // If the Deque was initially empty then new is both the top and bottom
    deque->bottom = new;
  }

  deque->top = new;
  deque->size++;
}

// Add an element to the bottom of a Deque
void deque_insert(Deque *deque, Data data) {
  Node *new = new_node(data);

  if (deque->size > 0) {
    new->prev = deque->bottom;
    deque->bottom->next = new;
  } else {
    // If the Deque was initially empty then new is both the top and bottom
    deque->top = new;
  }

  deque->bottom = new;
  deque->size++;
}

// Remove and return the top element from a Deque
Data deque_pop(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't pop from empty Deque");
  }

  Data data = deque->top->data;
  Node *old_top = deque->top;

  if (deque->size == 1) {
    deque->top = NULL;
    deque->bottom = NULL;
  } else {
    deque->top = old_top->next;
    deque->top->prev = NULL;
  }

  deque->size--;

  free(old_top);

  return data;
}

// Remove and return the bottom element from a Deque
Data deque_remove(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't remove from empty Deque");
  }

  Data data = deque->bottom->data;
  Node *old_bottom = deque->bottom;

  if (deque->size == 1) {
    deque->top = NULL;
    deque->bottom = NULL;
  } else {
    deque->bottom = old_bottom->prev;
    deque->bottom->next = NULL;
  }

  deque->size--;

  free(old_bottom);

  return data;
}

// Return the number of elements in a Deque
int deque_size(Deque *deque) {
  return deque->size;
}

// Print the Deque on its own line with the following format:
//   [x_1, x_2, ..., x_n]
//     ^              ^
//    top           bottom
void print_deque(Deque *deque) {
  Node *current = deque->top;
  int i = 0;

  printf("[");

  while (current) {
    printf("%d", current->data);
    // Print a comma unless we just printed the final element
    if (i < deque->size - 1) {
      printf(", ");
    }
    current = current->next;
    i++;
  }

  printf("]\n");
}

// Reverse the Deque using an iterative approach
void iterative_reverse(Deque *deque) {
	Node *node = deque->top;
	Node *tempnode;
	// iterate through each link in linked list
	// switch prev and next node links
	for (int i = 0; i < deque->size; i++) {
		tempnode = node -> prev;
		node -> prev = node -> next;
		node -> next = tempnode;
		node = node -> prev;
	}

	// switch the top and bot for deque
	tempnode = deque -> top;
	deque -> top = deque -> bottom;
	deque -> bottom = tempnode;
}

// Reverse the Deque using a recursive approach
void recursive_reverse(Deque *deque) {
	switch_links(deque -> top);
	Node *tempnode = deque -> top;
	deque -> top = deque -> bottom;
	deque -> bottom = tempnode;
}

// Own function
void switch_links(Node *node) {
	if (node == NULL) {
		return;
	}
	else {
		Node *tempnode = node -> prev;
		node -> prev = node -> next;
		node -> next = tempnode;
		return switch_links(node -> prev);
	}
}

// Split the Deque given a critical value k, such that the Deque contains
// all elements greater than equal to k above (i.e., closer to the top)
// the elements less than k.
//
// Within the two parts of the array (>= k and < k) the elements should
// be in their original order.
//
// This function must run in linear time.
void split_deque(Deque *deque, int k) {
	Node *greater_first_node=NULL,
			 *greater_last_node=NULL,
			 *less_first_node=NULL,
			 *less_last_node=NULL;

	Node *curr = deque->top;
	for (int i=0; i<deque->size; i++) {
		// greater or equal to k, put in top group
		if (curr->data >=k) {
			// first greater than equal to node
			if (greater_first_node == NULL) {
				greater_first_node = curr;
			}
			else {
			greater_last_node -> next = curr;
			curr -> prev = greater_last_node;
		}
		greater_last_node = curr;
		// printf("greater_first_node: %d\ngreater_last_node: %d\n", greater_first_node->data, greater_last_node->data);
		}
		// less than k, put in bottom group
		else {
			// first less than node
			if (less_first_node == NULL) {
				less_first_node = curr;
			}
			else {
			less_last_node -> next = curr;
			curr->prev = less_last_node;
		}
		less_last_node = curr;
		// printf("less_first_node: %d\nless_last_node: %d\n", less_first_node->data, less_last_node->data);
		}
		curr = curr -> next;
}
	// join the two groups in the middle
	if (less_last_node != NULL && greater_first_node !=NULL) {
		less_first_node -> prev = greater_last_node;
		greater_last_node -> next = less_first_node;
	}

	deque -> top = (greater_first_node != NULL? greater_first_node:less_first_node);
	deque -> bottom = (less_last_node != NULL? less_last_node : greater_last_node);
	deque -> top -> prev = NULL;
	deque -> bottom -> next = NULL;
}

// TODO: Add any other functions you might need for your Deque module
