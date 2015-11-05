#include "GA.h"

main()
{
  int i, j;
  int pop_size = 225;//개체 수
  int bit_count = 2;// 염색체 비트 수
  int data_count = 2;//염색체 데이터 수

  int board[15][15] = {0};

  population *pop = create_population(pop_size, bit_count, data_count);//개체군 생성

  rand_population(pop);//랜덤으로 개체군의 염색체 값 초기화

  for(i=0; i<pop_size; i++)
  {
    for(j=0; j<bit_count;j++)
    {
      if(j == bit_count/data_count)
      {
        printf(" ");
      }
      printf("%2d", pop->ivd[i].crms[j]);
    }
    printf("\n");
  }

  free_population(pop);

  printf("아무키나누르십시오...");getch();
}
