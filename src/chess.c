#include <stdlib.h>

#include "chess.h"

struct Chess *init_chess(void)
{
	struct Chess *chess = malloc(sizeof(struct Chess));
	verify_safe_malloc(chess);

	chess->bb = malloc(sizeof(struct Bitboards));
	verify_safe_malloc(chess->bb);
	chess->copy = malloc(sizeof(struct Bitboards));
	verify_safe_malloc(chess->copy);

	chess->curr = malloc(sizeof(struct Move));
	verify_safe_malloc(chess->curr);
	chess->prev = malloc(sizeof(struct Move));
	verify_safe_malloc(chess->prev);

	chess->orient = BLACK;
	chess->turn = WHITE;
	chess->ascii = true;
	return chess;
}

void destroy_chess(struct Chess *chess)
{
	free(chess->bb);
	free(chess->copy);
	free(chess->curr);
	free(chess->prev);
	free(chess);
}
