#include "GA.h"

main()
{
  int i, j;
  int pop_size = 3;//개체 수
  int bit_count = 2;// 염색체 비트 수
  int data_count = 2;//염색체 데이터 수

  int sum_x = 0, sum_y = 0, avg_x, avg_y;

  int x, y;
  int check = 0;

  int board[15][15] = {0};

  population *pop = create_population(pop_size, bit_count, data_count);//개체군 생성

  while(1)
  {
    sum_x = 0; sum_y = 0;
    if(!check)
    {
      rand_population(pop);//랜덤으로 개체군의 염색체 값 초기화
    }

    //display_population(pop);//개체군의 염색체 값 출력

    for(i=0; i<pop_size; i++)
    {
      sum_x += pop->ivd[i].crms[0];
      sum_y += pop->ivd[i].crms[1];
    }

    avg_x = sum_x / pop_size;
    avg_y = sum_y / pop_size;

    for(i=0; i<15; i++)
    {
      check = 0;
      for(j=0; j<15; j++)
      {
        if(board[avg_y][avg_x] == 'X' || board[avg_y][avg_x] == 'O')
	{
	  check = 1;
	  break;
	}
      }
      if(check == 1)
      {
      	break;
      }
    }
    if(check == 1)
    {
      continue;
    }

    printf("%d %d\n", avg_x, avg_y);

    printf("x : ");
    scanf("%d", &x);
    fflush(stdin);
    if(x<0 || x>14)
    {
      printf("ERROR\n");
      continue;
    }
    printf("y : ");
    scanf("%d", &y);
    fflush(stdin);
    if(y<0 || y>14)
    {
      printf("ERROR\n");
      continue;
    }

    if(avg_x == x && avg_y == y)
    {
      printf("ERROR\n");
      continue;
    }

    for(i=0; i<15; i++)
    {
      check = 0;
      for(j=0; j<15; j++)
      {
        if(board[y][x] == 'X' || board[y][x] == 'O')
	{
	  printf("ERROR\n");
	  check = 1;
	  break;
	}
      }
      if(check == 1)
      {
      	break;
      }
    }
    if(check == 1)
    {
      continue;
    }

    board[avg_y][avg_x] = 'X';
    board[y][x] = 'O';

/*    printf("   ");
    for(i=0; i<15; i++)
    {
      printf("%2d ", i);
    }
    printf("\n");

    for(i=0; i<15; i++)
    {
      printf("%2d ", i);
      for(j=0; j<15; j++)
      {
        printf("%2c ", board[i][j]);
      }
      printf("\n");
    }
    printf("\n");
  }*/
  free_population(pop);

  printf("아무키나누르십시오...");getch();
}
