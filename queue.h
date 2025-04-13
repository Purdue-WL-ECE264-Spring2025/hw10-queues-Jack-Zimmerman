#ifndef QUEUE_H_
#define QUEUE_H_

#include "linked_list.h"
#include "tile_game.h"

struct queue {
  struct linked_list data;
};

void enqueue(struct queue *q, struct game_state state);
struct game_state dequeue(struct queue *q);

int number_of_moves(struct game_state start);
int is_game_valid(struct game_state * game);
int is_visited(uint64_t * visited, int visited_size, uint64_t hash);

#endif