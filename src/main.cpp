#include <iostream>
#include <cstdlib>
#include <ctime>

#include "src/NQueens.cpp"
#include "src/genetic.cpp"

int main(int argc, char const *argv[])
{
  std::srand(std::time(0));

  Chromosome c = Genetic();

  // std::cout << c << std::endl;
  NQueens::drawBoard(std::cout, c.board);

  return 0;
}
