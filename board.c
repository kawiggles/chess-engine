#include "definitions.h"

#include "stdio.h"

int parseFen(char * fen, S_BOARD * pos) {
    ASSERT(fen != NULL);
    ASSERT(pos != NULL);

    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;

    resetBoard(pos);

    // First parse piece positions
    while ((rank >= RANK_1) && *fen) {
        int count = 1;
        
        switch (*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                      piece = EMPTY;
                      count = *fen - '0';
                      break;

            case '/':
            case ' ':
                      rank--;
                      file = FILE_A;
                      fen++;
                      continue;

            default:
                      printf("Invalid FEN input\n");
                      return -1;
        }

        for (int i = 0; i < count; i++) {
            int sq120 = SQ120(rank * 8 + file);
            if (piece != EMPTY) pos->pieces[sq120] = piece;
            file++;
        }
        fen++;
    }

    // Parse to-move indicator
    ASSERT(*fen == 'w' || *fen == 'b');

    pos->side = (*fen == 'w') ? WHITE : BLACK;
    fen += 2;

    // Parse castling permission
    for (int i = 0; i < 4; i++) {
        if (*fen == ' ') break;
        switch (*fen) {
            case 'K': pos->castlePerm |= WKCA;  break;
            case 'Q': pos->castlePerm |= WQCA;  break;
            case 'k': pos->castlePerm |= BKCA;  break;
            case 'q': pos->castlePerm |= BQCA;  break;
            default:                            break;
        }
        fen++;
    }
    fen++;

    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    // Parse en passant square
    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file >= FILE_A && file <= FILE_H);
        ASSERT(rank >= RANK_1 && rank <= RANK_8);

        pos->enPas = FR2SQ(file, rank);
    }

    pos->posKey = generatePosKey(pos);

    return 0;
}

void resetBoard(S_BOARD * pos) {
    for (int i = 0; i < BRD_SQ_NM; i++) {
        pos->pieces[i] = OFFBOARD;
    }

    for (int i = 0; i < 64; i++) {
        pos->pieces[SQ120(i)] = EMPTY;
    }

    for (int i = 0; i < 3; i++) {
        pos->bigPce[i] = 0;
        pos->majPce[i] = 0;
        pos->minPce[i] = 0;
        pos->pawns[i] = 0ULL;
    }

    for (int i = 0; i < 13; i++) {
        pos->pceNum[i] = 0;
    }

    pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

    pos->side = BOTH;
    pos->enPas = NO_SQ;
    pos->fiftyMove = 0;

    pos->ply = 0;
    pos->hisPly = 0;

    pos->castlePerm = 0;

    pos->posKey = 0ULL;
}

void printBoard(const S_BOARD * pos) {
    printf("\nGame Board:\n\n");
    
    for (int r = RANK_8; r >= RANK_1; r--) {
        printf("%d  ", r+1);
        for (int f = FILE_A; f <= FILE_H; f++) {
            int piece = pos->pieces[FR2SQ(f, r)];
            printf("%3c", PceChar[piece]);
        }
        printf("\n");
    }

    printf("\n   ");
    for (int f = FILE_A; f <= FILE_H; f++) printf("%3c", 'a' + f);
    printf("\n");
    printf("side: %c\n", SideChar[pos->side]);
    printf("enPas: %d\n", pos->enPas);
    printf("castle: %c%c%c%c\n",
            pos->castlePerm & WKCA ? 'K' : '-',
            pos->castlePerm & WQCA ? 'Q' : '-',
            pos->castlePerm & BKCA ? 'k' : '-',
            pos->castlePerm & BQCA ? 'q' : '-');
    printf("PosKey: %llX\n", pos->posKey);
}
