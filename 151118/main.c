#include "GA.h"

main()
{
  int i, j;
      pop_size = 10,//¿¿ ¿
      bit_count = 2,//¿¿¿¿ ¿¿ ¿
      data_count = 2;//¿¿¿¿ ¿¿¿ ¿

  int board[15][15] = {0};

  population *pop = create_population(pop_size, bit_count, data_count);//¿¿¿ ¿¿

  play_board(pop, board);//¿¿ ¿¿

  free_population(pop);//¿¿¿ ¿¿

  printf("¿¿¿¿ ¿¿¿¿¿...");getch();
}

