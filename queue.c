#include "queue.h"
#include "stdlib.h"
#include "tile_game.h"

int is_game_valid(struct game_state * game);
int is_visited(uint64_t * visited, int visited_size, uint64_t hash);

void enqueue(struct queue *q, struct game_state state) {
    insert_at_tail(&(q->data), (size_t)serialize(state));
}

struct game_state dequeue(struct queue *q) {
    return deserialize(remove_from_head(&(q->data)));
}

int number_of_moves(struct game_state start) {  
    uint64_t *  visited = (uint64_t*)malloc(sizeof(uint64_t) * 500000);

    int visited_size = 0;
    struct queue game;
    game.data.head = NULL;

    enqueue(&game, start);

    //while the queue is not empty
    while (game.data.head){
        //pop end to check if we passed
        struct game_state dq = dequeue(&game);

        if (is_game_valid(&dq)){
            free(visited);
            free_list(game.data);
            return dq.num_steps;
        }
        else if (is_visited(visited, visited_size, serialize(dq))){
            continue;
        } 
        else{
            visited[visited_size++] = serialize(dq);
            //add all possible steps
            struct game_state down_state = dq;
            move_down(&down_state);
            enqueue(&game, down_state);

            struct game_state up_state = dq;
            move_up(&up_state);
            enqueue(&game, up_state);

            struct game_state left_state = dq;
            move_left(&left_state);
            enqueue(&game, left_state);

            struct game_state right_state = dq;
            move_right(&right_state);
            enqueue(&game, right_state);
        }
    }

    
   free(visited);
   return 0;
}

int is_game_valid(struct game_state * game){
    if (game->tiles[3][3] != 0){
        return 0;
    }

    for (int a = 0; a < 4; a++){
        for (int b = 0; b < 4; b++){
            if (a == 3 && b == 3) {
                return 1;
            }
            else if (game->tiles[a][b] != (a*4) + (b+1)){
                return 0;
            }
        }
    }

    return 0;
}

int is_visited(uint64_t * visited, int visited_size, uint64_t hash){
    for (int i = visited_size-1; i >= 0; i--){
        if (hash == visited[i]){
            return 1;
        }
    }
    
    return 0;
}
