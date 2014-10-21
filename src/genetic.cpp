#include <set>

#include "NQueens.h"

class Chromosome {
public:
  Chromosome(NQueens::board_t board)
    : board(board), value(NQueens::score(board))
  {
  }

  const NQueens::board_t board;
  const int value;

  inline bool operator<(const Chromosome& rhs) const
  {
    return value < rhs.value;
  }
};

typedef std::multiset<Chromosome> population_t;
const int population_size = 100;

void fill_initial_population(population_t * population)
{
  auto local_population_size = population_size;
  if(local_population_size > 2) 
  {
    population->emplace(0);
    population->emplace(NQueens::board_mask);
    local_population_size -= 2;
  }

  for (int i = 0; i < local_population_size; ++i)
  {
    population->emplace(NQueens::randomBoard());
  }
}

Chromosome fullrandom_crossingover(const Chromosome& one, const Chromosome& two)
{
  #define set_bits(a, b) (((a) & NQueens::board_mask) & ((b) & NQueens::board_mask))
  #define mix(a, b, shift) (set_bits((a), (shift)) | set_bits((b), ~(shift)))

  NQueens::board_t shift = NQueens::randomBoard();  
  NQueens::board_t new_board = mix(one.board, two.board, shift);
  return Chromosome(new_board);
}

Chromosome half_crossingover(const Chromosome& one, const Chromosome& two)
{
  NQueens::board_t new_board = (one.board & 0x00FFF000) | (two.board & 0x00000FFF);
  return Chromosome(new_board);
}

Chromosome random_single_crossingover(const Chromosome& one, const Chromosome& two)
{
  NQueens::board_t split_mask = ((1 << ((rand() % 22) + 1)) - 1);
  NQueens::board_t new_board = (one.board & (split_mask & NQueens::board_mask)) | 
                                (two.board & (~split_mask & NQueens::board_mask));
  return Chromosome(new_board);
}

Chromosome mutate(const Chromosome& source)
{
  NQueens::board_t new_board = source.board;
  NQueens::moveRandomQueenRandomly(new_board);
  return Chromosome(new_board);
}

void print_population(const population_t& population)
{
  for (auto i = population.cbegin(); i != population.cend(); ++i)
  {
    std::cout << (*i).value << " ";
  }
  std::cout << std::endl;
}

Chromosome subling(const Chromosome& one, const Chromosome& two)
{
  if((rand() % 10) == 0) { // mutate
    return mutate(random_single_crossingover(one, two));
  } else { // no mutate
    return random_single_crossingover(one, two);
  }
}

bool population_same(const population_t& population)
{
  int local_value;
  auto i = population.cbegin();
  local_value = (*i).value;
  ++i;
  for (; i != population.cend(); ++i)
  {
    if((*i).value != local_value) return false;
  }

  return true;
}

bool population_contains_optimal(const population_t& population)
{
  auto i = population.cbegin();
  return (*i).value == 0;
}

const Chromosome& random_high_fitness_chromosome(const population_t& population)
{
  auto best = population.cbegin();
  auto c = population.count(*best);

  if(c == 1)
  {
    return *best;
  }

  int distance = rand() % (c - 1);
  // std::cout << "D: " << distance << " from " << (c - 1) << std::endl;
  std::advance(best, distance);
  return *best;
}

const Chromosome& random_any_fitness_chromosome(const population_t& population)
{
  auto chosen = population.cbegin();

  int distance = rand() % (population.size() - 1);
  std::advance(chosen, distance);
  return *chosen;
}

const Chromosome& random_first_half_fitness_chromosome(const population_t& population)
{
  auto chosen = population.cbegin();

  int distance = rand() % (population.size()/2 - 1);
  std::advance(chosen, distance);
  return *chosen;
}

Chromosome Genetic()
{
  population_t * current_population = new population_t;
  fill_initial_population(current_population);

  bool stop = false;
  while(!stop) {
    population_t * next_population = new population_t;

    for (int i = 0; i < population_size/2; ++i)
    {
      auto one = random_first_half_fitness_chromosome(*current_population);
      auto two = random_first_half_fitness_chromosome(*current_population);

      next_population->insert(subling(one, two));
      next_population->insert(subling(one, two));
    }
    delete current_population;
    current_population = next_population;

    // std::cout << "==========" << std::endl;
    // print_population(*current_population);

    // auto board = (*(current_population->cbegin())).board;
    // std::cout << "Score: " << NQueens::score(board) << std::endl;
    // NQueens::printBoard(std::cout, board);
    // NQueens::drawBoard(std::cout, board);

    if(population_contains_optimal(*current_population)) { stop = true; }
  }
  return *current_population->cbegin();
}
