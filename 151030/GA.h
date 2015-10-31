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

population* create_population(int pop_size, int bit_count, int data_count);
void free_population(population *pop);

#endif
