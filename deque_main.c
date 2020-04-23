#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

int main(int argc, char *argv[]) {

  Deque *trial = new_deque();
  deque_insert(trial, 1);
  deque_insert(trial, 4);
  deque_insert(trial, 3);
  deque_insert(trial, 2);
  deque_insert(trial, 5);

  print_deque(trial);
  split_deque(trial, 2);
  print_deque(trial);

  return 0;
}
