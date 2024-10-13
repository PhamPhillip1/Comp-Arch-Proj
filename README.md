# Checkers Game for Fall 2024 CS 3503 Computer Organization and Architecture 

## Introduction
This project is a classic checkers game written in the C language. The game supports two player and uses bitboard implementation for efficient game state representation. 

## Purpose of the Project
- Opportunity to enhance C programming skills
- Explore game development concepts
- Get a better understanding of bitwise operations and binary arithmethic and applying it

## Game Rules
- Player 1 is black and Player 2 is red. The user moves by typing in the original position and the destination position ranging from 0 to 63.
- Promotion to king are made when the player's piece reaches the low row on the other side. King pieces are represented by first letter of the color followed by a 'K' (Ex. BK).
- Pieces move diagonally and piece captures occur when a player's piece jumps the opponent's piece.
- Game ends when the opponent has no more pieces left.

## Method Design
- InitializeBoard() and PrintBoard(): Prints an 8x8 checkers board where the player's pieces are represented using 64-bit integers (U64)
- MovePiece(): Handles king conversions when pieces reaches other side of the board and piece capturing
- CapturePiece(): A helper method assisting in game logic for MovePiece() when piece capture is valid
- isLegalMove(): Ensures that move doesn't go out of bounds, doesn't go to an occupied space, and move diagonally
- UpdateGameState(): Checks for game ending conditions and make sure player turn switches
