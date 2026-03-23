#include "definitions.h"

int Sq120ToSq64[BRD_SQ_NM];
int Sq64ToSq120[64];

void initSq120To64() {
    for (int i = 0; i < BRD_SQ_NM; i++) {
        Sq120ToSq64[i] = 65;
    }

    for (int i = 0; i < 64; i++) {
        Sq64ToSq120[i] = 120;
    }

    int sq64 = 0;
    for (int rank = RANK_1; rank <= RANK_8; rank++) {
        for(int file = FILE_A; file <= FILE_H; file++) {
            int sq = FR2SQ(file,rank);
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }
}

void AllInit() {
    initSq120To64();
}
