#include "GA.h"

main()
{
  int i, j,
      pop_size = 10,//개체 수
      bit_count = 2,//염색체 내의 비트 수
      data_count = 2;//염색체 내의 데이터 수

  int board[15][15];
  
  //board 배열 안의 모든 값을 ' '으로 초기화 해준다.
  for(i=0; i<15; i++)
  {
    for(j=0; j<15; j++)
    {
      board[i][j] = ' ';
    }
  }

  population *pop = create_population(pop_size, bit_count, data_count);//개체군 생성

  play_board(pop, board);//플레이!

  free_population(pop);
}

