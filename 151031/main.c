#include "GA.h"

main()
{
  int i;
  int pop_size = 225;
  int bit_count = 8;
  int data_count = 2;

  int board[15][15] = {0};

  population *pop = create_population(pop_size, bit_count, data_count);

  for(i=0; i<pop_size; i++)
  {
  }

  free_population(pop);

  printf("아무키나누르십시오...");getch();
}
