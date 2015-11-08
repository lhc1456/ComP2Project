#include "GA.h"

main()
{
  int i, j;
  int pop_size = 3;//개체 수
  int bit_count = 2;// 염색체 비트 수
  int data_count = 2;//염색체 데이터 수

  int sum_x = 0, sum_y = 0, avg_x, avg_y;

  int x, y;
  int check = 0;//랜덤 개체군을 뽑을 것인지와 반복문을 빠져나가기 위한 값

  int board[15][15] = {0};

  population *pop = create_population(pop_size, bit_count, data_count);//개체군 생성

  while(1)
  {
    sum_x = 0; sum_y = 0;
    if(check == 0 || check == 2)//0과 1이외의 값일때에는 염색체 값을 초기화 하지 않는다.
    {
      rand_population(pop);//랜덤으로 개체군의 염색체 값 초기화
    }

    //display_population(pop);//개체군의 염색체 값 출력

    if(check == 0)
    {
      printf("-9999입력시 종료\n");
      printf("x : ");
      scanf("%d", &x);
      if(x == -9999)
      {
        printf("종료합니다\n");
        break;
      }
      if(x<0 || x>14)
      {
        printf("ERROR\n");
        check = 2;//범위를 넘겼을 경우 check를 2로 주며 다시 반복문을 시행한다.
        continue;
      }
      printf("y : ");
      scanf("%d", &y);
      if(y == -9999)
      {
        printf("종료합니다\n");
        break;
      }
      if(y<0 || y>14)
      {
        printf("ERROR\n");
        check = 2;
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
	    check = 2;//입력한 값이 판 위에 존재한다면 check를 2로 주고 다시 반복문을 시행한다.
	    break;
  	  }
        }
        if(check == 2)
        {
          break;
        }
      }
      if(check == 2)
      {
        continue;
      }
    }

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
	  check = 2;
	  break;
	}
      }
      if(check == 2)
      {
      	break;
      }
    }
    if(check == 2)
    {
      continue;
    }
    
    if(avg_x == x && avg_y == y)
    {
      check = 2;//컴퓨터의 값과 겹치는 경우 check를 2로 주며 다시 반복문을 시행한다.
      continue;
    }

    printf("%d %d\n", avg_x, avg_y);

    board[avg_y][avg_x] = 'X';//모든 예외처리가 끝나면 board에 값을 집어넣는다. 상대와 나를 구분하기위해X와O로 나누어 값을 준다.
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
    printf("\n");*/
    check = 0;
  }
  free_population(pop);

  printf("아무키나누르십시오...");getch();
}
