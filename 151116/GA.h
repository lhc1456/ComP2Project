#ifndef GA_H
#define GA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef int bit;

/*염색체*/
typedef bit chromosome;

/*개체*/
typedef struct
{
  chromosome *crms;
  double fitness;//적응도
}individual;

/*개체군*/
typedef struct
{
  individual *ivd;
  int pop_size;//개체 수
  int bit_count;//염색체의 비트 수
  int data_count;//염색체 내의 데이터 수
}population;

/*개체군 생성 : 메모리를 할당하고 리턴해줍니다. make : 151030*/
population* create_population(int pop_size, int bit_count, int data_count)
{
  int i;

  population *pop = (population*)malloc(sizeof(population));
  individual *ivd = (individual*)malloc(sizeof(individual)*pop_size);

  for(i=0; i<pop_size; i++)
  {
    ivd[i].crms = (int*)malloc(sizeof(chromosome)*bit_count);
    ivd[i].fitness = 0.0;
  }

  pop->ivd = ivd;
  pop->pop_size = pop_size;
  pop->bit_count = bit_count;
  pop->data_count = data_count;

  return pop;
}

/*개체군의 메모리를 해제합니다. make : 151030*/
void free_population(population *pop)
{
  int i;

  for(i=0; i<pop->pop_size; i++)
  {
    free(pop->ivd[i].crms);
  }
  free(pop->ivd);
  free(pop);
}

/*a와 b사이의 작은 값을 리턴합니다. make : 151031*/
int min(int a, int b)
{
  return (a<b) ? a:b;
}

/*a와 b사이에 존재하는 수 하나를 랜덤하게 추출합니다. make : 151031*/
int rand_between(int a, int b)
{
  int delta, randnum;

  delta = abs(a-b)+1;
  randnum = rand()%delta;

  return (min(a,b)+randnum);
}

/*개체들의 염색체를 랜덤하게 초기화합니다. make : 151031*/
void rand_population(population *pop)
{
  int i;
  int pos;

  srand(time(NULL));

  for(i=0; i<pop->pop_size;i++)
  {
    for(pos=0; pos<pop->bit_count; pos++)
    {
      pop->ivd[i].crms[pos] = rand_between(0,14);
    }
  }
}

/*개체군의 개체들 값을 전부 출력합니다. make: 151105*/
void display_population(population *pop)
{
  int i, j;

  for(i=0; i<pop->pop_size; i++)
  {
    for(j=0; j<pop->bit_count; j++)
    {
      if(j == 1)
      {
        printf(" ");
      }
      printf("%2d", pop->ivd[i].crms[j]);
    }
    printf("\n");
  }
}

/*돌연변이, XOR연산으로 값을 뒤바꾸어 준다. make : 151107*/
void mutate(chromosome *crms, int bit_count)
{
  int i;

  for(i=0; i<bit_count; i++)
  {
    if(rand_between(0, 300) == 0)
    {
      crms[i] ^= 14;
    }
  }
}

/*적응도 함수로 개체에 적응도를 더해줍니다. make : 151108*/
void fitness_func(population *pop, int x, int y)
{
  int i;
  double fit;

  for(i=0; i<pop->pop_size; i++)
  {
    fit = hypot(pop->ivd[i].crms[0] - x, pop->ivd[i].crms[1]);
    if(fit > 1 && fit < 1.5)
    {
      pop->ivd[i].fitness += 1;
    }
  }
}

/*플레이어와 컴퓨터가 순서대로 돌을 둔다. make : 151109*/
void play_board(population *pop, int (*board)[15])
{
  int i, j;
  int x, y;
  int check = 0;
  int sum_x, sum_y, avg_x, avg_y;

  while(1)
  {
    sum_x = 0; sum_y = 0;
    if(check == 0 || check == 2)//0과 1이외의 값일때에는 염색체 값을 초기화 하지 않는다.
    {
      rand_population(pop);//랜덤으로 개체군의 염색체 값 초기화
    }

    //display_population(pop);//개체군의 염색체 값 출력

    if(check == 0 || check == 1)
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
	    printf("%d %d\n", avg_x, avg_y);
            check = 1;//입력한 값이 판 위에 존재한다면 check를 2로 주고 다시 반복문을 시행한다.
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
    }

    for(i=0; i<pop->pop_size; i++)
    {
      sum_x += pop->ivd[i].crms[0];
      sum_y += pop->ivd[i].crms[1];
    }

    avg_x = sum_x / pop->pop_size;
    avg_y = sum_y / pop->pop_size;

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
      check = 1;//컴퓨터의 값과 겹치는 경우 check를 2로 주며 다시 반복문을 시행한다.
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
}

/*교배할 개체 선택한다. make : 151111*/
individual* select_individual(population *pop)
{
  unsigned int index1, index2;
  int i, count = 0;

  do
  {
    count++;

    index1 = rand_between(0, pop->pop_size-1);
    index2 = rand_between(0, pop->pop_size-1);

    if(pop->ivd[index1].fitness == 0)
    {
      break;
    }

    if(count > 3)
    {
      for(i=0; i<pop->pop_size; i++)
      {
        mutate(pop->ivd[i].crms, pop->bit_count);
      }
      break;
    }
  }while(pop->ivd[index1].fitness == pop->ivd[index2].fitness);

  if(pop->ivd[index1].fitness > pop->ivd[index2].fitness)
  {
    return &pop->ivd[index1];
  }
  else
  {
    return &pop->ivd[index2];
  }
}

/*두 개의 염색체를 교배하여 새로운 두 개의 염색체로 만듭니다.*/
void crossover(chromosome *old_c1, chromosome *old_c2, chromosome *new_c1, chromosome *new_c2, int bit_count)
{
  int i,
      pos;

//염색체의 데이터를 복제합니다.
  for(i=0; i<bit_count; i++)
  {
    new_c1[i] = old_c2[i];
    new_c2[i] = old_c1[i];
  }
//교배할 위치를 선택합니다.
  pos = rand_between(0, bit_count-1);
//특정 위치(pos)의 데이터를 교배합니다.
  new_c1[pos] = old_c1[pos];
  new_c2[pos] = old_c2[pos];
}

/*두 개체를 교배 또는 돌연변이를 가미해서 배양합니다.*/
void breed(individual *old_v1, individual *old_v2, individual *new_v1, individual *new_v2, int bit_count)
{
  //교배시킨다.
  crossover(old_v1->crms, old_v2->crms, new_v1->crms, new_v2->crms, bit_count);
  //돌연변이를 가한다.
  mutate(new_v1->crms, bit_count);
  mutate(new_v2->crms, bit_count);
}

/*새로운 세대를 만든다.*/
void new_generate(population *old_pop, population *new_pop)
{
  int i;
  individual *v1, *v2;

  //랜덤하게 2개의 개체를 pop_size/2번 선택한다.
  for(i=0; i<old_pop->pop_size; i+=2)
  {
    //배양할 개체 쌍을 선택한다.
    v1 = select_individual(old_pop);
    v2 = select_individual(old_pop);
    //배양해서 개체군의 개체를 만들고 새로운 세대를 만든다.
    breed(v1, v2, &new_pop->ivd[i], &new_pop->ivd[i+1], old_pop->bit_count);
  }
}

#endif
