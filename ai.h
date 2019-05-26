#ifndef AI_H
#define AI_H

namespace ai{

int evaluate(int* board);
int minmax(int* board, int depth, bool max);
}
#endif // AI_H
