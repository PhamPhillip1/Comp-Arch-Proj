#include <stdio.h>
#include <stdint.h>
#include "utility.h"

//Link utility and checkers files
//gcc -o CheckersGame Checkers.o utility.o
//./CheckersGame

// Define bitboard
#define U64 unsigned long long

void InitializeBoard(U64 *bitboard) {
    // All pieces to zero
    bitboard[0] = 0ULL; // Player 1 (black pieces)
    bitboard[1] = 0ULL; // Player 2 (red pieces)

    // Set Player 1 pieces in ranks 0, 1, and 2
    for (int rank = 0; rank < 3; rank++) {
        for (int file = 0; file < 8; file++) {
            if ((rank + file) % 2 != 0) { // Pieces in odd square
                bitboard[0] |= (1ULL << (rank * 8 + file)); // Set bit for Player 1
            }
        }
    }

    // Set Player 2 pieces in ranks 5, 6, and 7
    for (int rank = 5; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            if ((rank + file) % 2 != 0) { // Pieces in odd square
                bitboard[1] |= (1ULL << (rank * 8 + file)); // Set bit for Player 2
            }
        }
    }

}

void PrintBoard(U64 *bitboard, U64 *kings) {
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            int squareIndex = rank * 8 + file;

            // Check for red pieces and black pieces
            int isBlack = (bitboard[0] & (1ULL << squareIndex)) ? 1 : 0;
            int isRed = (bitboard[1] & (1ULL << squareIndex)) ? 1 : 0;
            int isBlackKing = (kings[0] & (1ULL << squareIndex)) ? 1 : 0;
            int isRedKing = (kings[1] & (1ULL << squareIndex)) ? 1 : 0;

            if (isRedKing) {
                printf("RK "); // Print 'RK' for red king pieces
            } else if (isRed) {
                printf("R "); // Print 'R' for red pieces
            } else if (isBlackKing) {
                printf("BK "); // Print 'BK' for black king pieces
            } else if (isBlack) {
                printf("B "); // Print 'B' for black pieces
            } else {
                printf(". "); // Print '.' for empty spaces
            }
        }
        printf("\n");
    }
}

void CapturePiece(U64* bitboard, int midSquare, int player) {
   // If player is 0, opponent is 1 and vice versa
   int opponent = (player == 0) ? 1 : 0;

   // Check if opponent piece is in square
   if (bitboard[opponent] & (1ULL << midSquare)) {
     // removes opponent piece from board
     bitboard[opponent] = ClearBit(bitboard[opponent], midSquare);
     printf("Piece has been captured at position %d.\n", midSquare);
   } 
} 

void MovePiece(U64 *bitboard, U64 *kings, int ogSquare, int destSquare, int player) {
  // Checks if there is a piece at ogSquare for current player
  if (!(bitboard[player] & (1ULL << ogSquare))) {
    printf("There is no piece here for player %d.\n", player + 1);
    return;
  }

  // Remove piece from OG spot
  bitboard[player] = ClearBit(bitboard[player], ogSquare);

  // Add piece to destination spot
  bitboard[player] = SetBit(bitboard[player], destSquare);

  // Promote to king
  if (player == 0 && destSquare >= 56 && destSquare <= 63) {
        kings[0] = SetBit(kings[0], destSquare); // Set king piece in player 1's king bitboard
        printf("Player's 1 piece has been promoted to King at position %d.\n", destSquare);
  } else if (player == 1 && destSquare >=0 && destSquare <= 7) {
        kings[1] = SetBit(kings[1], destSquare); // Set king piece in player 2's king bitboard
        printf("Player 2's piece has been promoted to King at position %d.\n", destSquare);
  }

  // Code downwards is for piece capture
  int opponent = (player == 0) ? 1 : 0; // If player 1, opponent 2 and vice versa
  int midSquare = (ogSquare + destSquare) / 2; // Gets the spot bewteen og and dest

  // Captured distance can only be 14 or 18 ("Jumping over")
  int capturedDistance = destSquare - ogSquare;

  // Checks for valid capture distance
  if ((player == 0) && (capturedDistance == 14 || capturedDistance == 18)) {
    CapturePiece(bitboard, midSquare, player);
  }

  if ((player == 1) && (capturedDistance == -14 || capturedDistance == -18)) {
    CapturePiece(bitboard, midSquare, player);
  }
}

int isLegalMove(U64* bitboard,U64 *kings, int ogSquare, int destSquare, int player) {
    // Check start and end squares are valid sqaures
    if (ogSquare < 0 || ogSquare > 63 || destSquare < 0 || destSquare > 63) {
        printf("You have chosen a square outside of the board, player %d.\n", player + 1);
        return 0; 
    }

    // Checks if end square is occupied
    if ((bitboard[0] & (1ULL << destSquare)) || (bitboard[1] & (1ULL << destSquare))) {
        printf("You cannot move here, Player %d.\n", player + 1);
        return 0;
    }

    // Calculates the row and column of where the square is at
    int ogSquareRow = ogSquare / 8;
    int ogSquareCol = ogSquare % 8;
    int destSquareRow = destSquare / 8;
    int destSquareCol = destSquare % 8;

    // Checks if it's a diagonal move
    // If the difference of the row and col is the same, its diagonal
    if ((destSquareRow - ogSquareRow) != (destSquareCol - ogSquareCol)) {
        printf("This move is not diagonal.\n");
        return 0;
    }
        return 1;
   }

   int UpdateGameState(U64* bitboard,U64 *kings, int currentPlayer) {
    // Checks if player 1 or player 2 have no pieces left
    if (bitboard[0] == 0ULL & kings[0] == 0ULL) {
        printf("Player 2 wins! No more pieces for player 1.\n");
        return -1;
    }

    if (bitboard[1] == 0ULL & kings[1] == 0ULL) {
        printf("Player 1 wins! No more pieces for player 2.\n");
        return -1;
    }

    // Switches player
    currentPlayer = (currentPlayer == 0) ? 1 : 0;
    printf("It is now Player %d's turn.\n", currentPlayer + 1);
    return currentPlayer;
   }      

int main() {
    int player1 = 0, player2 = 1, currentPlayer = player1;
    int ogSquare, destSquare;
    int capturedPieces = 0;
    U64 bitboard[2] = {0ULL, 0ULL}; // Create an array to hold both bitboards 
    U64 kings[2] = {0ULL, 0ULL}; // Two king bitboard for two player

    InitializeBoard(bitboard);

   do {
        char binaryOutput [65];
        char hexOutput [17];

        PrintBoard(bitboard, kings);

        // Convert Player 1's bitboard to binary and hexadecimal and print it
        ToBinaryString(bitboard[0], binaryOutput);
        ToHexString(bitboard[0], hexOutput);
        printf("\nPlayer 1's bitboard in binary:\n%s\n", binaryOutput);
        printf("Player 1's bitboard in hexadecimal:\n%s\n", hexOutput);

        // Convert Player 1's king bitboard to binary and hexadecimal and print it
        ToBinaryString(kings[0], binaryOutput);
        ToHexString(kings[0], hexOutput);
        printf("\nPlayer 1's king bitboard in binary:\n%s\n", binaryOutput);
        printf("Player 1's king bitboard in hexadecimal:\n%s\n", hexOutput);

        // Convert Player 2's bitboard to binary and hexadecimal and print it
        ToBinaryString(bitboard[1], binaryOutput);
        ToHexString(bitboard[1], hexOutput);
        printf("\nPlayer 2's bitboard in binary:\n%s\n", binaryOutput);
        printf("Player 2's bitboard in hexadecimal:\n%s\n", hexOutput);

        // Convert Player 2's king bitboard to binary and hexadecimal and print it
        ToBinaryString(kings[1], binaryOutput);
        ToHexString(kings[1], hexOutput);
        printf("\nPlayer 2's king bitboard in binary:\n%s\n", binaryOutput);
        printf("Player 2's king bitboard in hexadecimal:\n%s\n", hexOutput);
        printf("\n");

        
        printf("Player %d, where do you want to move?\nEnter the original square and destiination square to proceed: ", currentPlayer + 1);
        scanf("%d %d", &ogSquare, &destSquare);

        if(isLegalMove(bitboard, kings, ogSquare, destSquare, currentPlayer)) {
            MovePiece(bitboard, kings, ogSquare, destSquare, currentPlayer);
        } 

        int nextTurn = UpdateGameState(bitboard, kings, currentPlayer);
        if(nextTurn == -1) {
            break;
        }
        currentPlayer = nextTurn;

    } while (capturedPieces != 12);
        
    return 0;
}
