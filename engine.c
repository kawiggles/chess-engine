#include "stdio.h"
#include "stdlib.h"
#include "definitions.h"

int main() {
    
    AllInit();

    U64 playBitBoard = 0ULL;

    int PieceOne = rand();
    int PieceTwo = rand();
    int PieceThree = rand();
    int PieceFour = rand();

    printf("PieceOne: %X\n", PieceOne);
    printf("PieceTwo: %X\n", PieceTwo);
    printf("PieceThree: %X\n", PieceThree);
    printf("PieceFour: %X\n", PieceFour);

    printBitBoard(playBitBoard);

    return 0;
}
