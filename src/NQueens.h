#pragma once

/*
  Layout:

    desc: Full diagonal board example
    board dig: 16434824
    board bin: 0b111110101100011010001000

    pos:    7   6   5   4   3   2   1   0
    val:    7   6   5   4   3   2   1   0
    bits: 111 110 101 100 011 010 001 000


    desc: Solved task example
    board dig: 6761440
    board bin: 0b011001110010101111100000

    pos:    7   6   5   4   3   2   1   0
    val:    3   1   6   2   5   7   4   0
    bits: 011 001 110 010 101 111 100 000

*/

class NQueens
{
public:
  typedef uint32_t board_t;

  static inline uint8_t height(const board_t& board, const uint8_t queen_num);

  static inline void setHeight(board_t& board, const uint8_t queen_num, const uint8_t height);

  static void printBoard(std::ostream& stream, board_t board);

  static void drawBoard(std::ostream& stream, board_t board);

  static const int max_score;
  static int score(const board_t& board);

  static inline void moveRandomQueenRandomly(board_t& board);

  static const board_t board_mask;
  static board_t randomBoard();
};
