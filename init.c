#include "definitions.h"
#include "stdlib.h"

/* rand() only generates 15 random bits, so we generate a random number for 
 * each 15 bit section of the 64 bit number and shift it some amount of bits 
 * over to fill in each part of the 64 bits
 */
# define RAND_64 (  (U64) rand() + \
                    (U64) rand() << 15 + \
                    (U64) rand() << 30 + \
                    (U64) rand() << 45 + \
                    ( (U64) rand() & 0xf) << 60     )

int Sq120ToSq64[BRD_SQ_NM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

void initHashKeys() {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 120; j++) PieceKeys[i][j] = RAND_64;
    }
    SideKey = RAND_64;
    for (int i = 0; i < 16; i++) CastleKeys[i] = RAND_64;
}

void initBitMasks() {
    for (int i = 0; i < 64; i++) {
        SetMask[i] = 0ULL;
        ClearMask[i] = 0ULL;
    }

    for (int i = 0; i < 64; i++) {
        SetMask[i] = (1ULL << i);
        ClearMask[i] = ~SetMask[i];
    }
}

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
    initBitMasks();
    initHashKeys();
}
