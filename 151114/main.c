#include "GA.h"

main()
{
  int i, j;
  int pop_size = 10;//개체 수
  int bit_count = 2;// 염색체 비트 수
  int data_count = 2;//염색체 데이터 수

  int sum_x = 0, sum_y = 0, avg_x, avg_y;

  int x, y;
  int check = 0;//랜덤 개체군을 뽑을 것인지와 반복문을 빠져나가기 위한 값

  int board[15][15] = {0};

  population *pop = create_population(pop_size, bit_count, data_count);//개체군 생성

  play_board(pop, board);

  free_population(pop);

  printf("옜옜 옜옜�...");getch();
}

