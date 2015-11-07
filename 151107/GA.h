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

/*개체군 생성 : 메모리를 할당하고 리턴해줍니다.*/
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

/*개체군의 메모리를 해제합니다.*/
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

/*a와 b사이의 작은 값을 리턴합니다.*/
int min(int a, int b)
{
  return (a<b) ? a:b;
}

/*a와 b사이에 존재하는 수 하나를 랜덤하게 추출합니다.*/
int rand_between(int a, int b)
{
  int delta, randnum;

  delta = abs(a-b)+1;
  randnum = rand()%delta;

  return (min(a,b)+randnum);
}

/*개체들의 염색체를 랜덤하게 초기화합니다.*/
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

/*개체군의 개체들 값을 전부 출력합니다.*/
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

/*돌연변이, XOR연산으로 값을 뒤바꾸어 준다.*/
void mutate(chromosome *crms, int bit_count)
{
  int i;

  for(i=0; i<bit_count; i++)
  {
    if(rand_between(0, 300) == 0)
    {
      crms[i] ^= 15;
    }
  }
}

#endif
