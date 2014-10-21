#include <iostream>
#include <bitset>

#include "NQueens.h"

inline uint8_t NQueens::height(const NQueens::board_t& board, const uint8_t queen_num)
{
  const auto shift = queen_num * 3;
  return (board & (0x7 << shift)) >> shift;
}

inline void NQueens::setHeight(NQueens::board_t& board, const uint8_t queen_num, const uint8_t height)
{
  const auto shift = queen_num * 3;
  const NQueens::board_t board_part = (board & (0x7 << shift)) ^ (height << shift);
  board ^= board_part;
}

inline void NQueens::printBoard(std::ostream& stream, NQueens::board_t board)
{
  for (int i = 0; i < 8; ++i)
  {
    int height = board & 0x7;
    stream << "Pos: " << i << "; Height: " << height << " (bin: " << std::bitset<3>(height) << ")" << std::endl;
    board >>= 3;
  }
}

inline void NQueens::drawBoard(std::ostream& stream, NQueens::board_t board)
{
  std::bitset<64> bit_board(0);

  // x - queen
  // y - height
  for (int x = 0; x < 8; ++x)
  {
    const int y = int(board & 0x7);
    bit_board[y * 8 + x] = true;
    // stream << "Assign: [" << x << ", " << y << "]" << std::endl;
    board >>= 3;
  }

  for (int y = 0; y < 8; ++y)
  {
    for (int x = 0; x < 8; ++x)
    {
      char value = bit_board[(7-y) * 8 + x] ? 'q' : '.';
      stream << value;
    }
    stream << std::endl;
  }
}


const int NQueens::max_score = 28;
int NQueens::score(const NQueens::board_t& board)
{
  int val = 0;
  NQueens::board_t local_board = board;

  for (int queen = 0; queen < 8; ++queen)
  {
    const int height = int(local_board & 0x7);

    for (int shift = 1; shift < 8; ++shift)
    {
      #define rule(test) { if(NQueens::height(board, shifted) == (test)) { val++; } }

      {
        const int shifted = queen + shift;
        if(shifted < 8) {
          rule(height + shift)
          rule(height - shift)
          rule(height)
        }
      }

      // {
      //   const int shifted = queen - shift;
      //   if(shifted >= 0) {
      //     rule(height + shift)
      //     rule(height - shift)
      //     rule(height)
      //   }
      // }
    }
    local_board >>= 3;
  }

  return val;
}

void NQueens::moveRandomQueenRandomly(board_t& board)
{
  setHeight(board, rand() & 0x7, rand() & 0x7);
}

const NQueens::board_t NQueens::board_mask = 0x00FFFFFF;
NQueens::board_t NQueens::randomBoard()
{
  const board_t board(rand() & board_mask);
  // std::bitset<32> bit_board(board);
  // std::cout << bit_board << std::endl;
  return board;
}

