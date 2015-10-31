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

#endif
