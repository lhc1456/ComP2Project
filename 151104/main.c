#include "GA.h"

main()
{
  int i, j;
  int pop_size = 225;
  int bit_count = 2;
  int data_count = 2;

  int board[15][15] = {0};

  population *pop = create_population(pop_size, bit_count, data_count);

  rand_population(pop);

  for(i=0; i<pop_size; i++)
  {
    for(j=0; j<bit_count;j++)
    {
      if(j == bit_count/data_count)
      {
        printf(" ");
      }
      printf("%d", pop->ivd[i].crms[j]);
    }
    printf("\n");
  }

  free_population(pop);

  printf("아무키나누르십시오...");getch();
}
