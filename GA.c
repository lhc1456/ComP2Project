#include "GA.h"

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

int min(int a, int b)
{
  return (a<b) ? a:b;
}

int rand_between(int a, int b)
{
  int delta, randnum;

  delta = abs(a-b)+1;
  randnum = rand()%delta;

  return (min(a,b)+randnum);
}

void rand_population(population *pop)
{
  int i;
  int pos;

  srand(time(NULL));

  for(i=0; i<pop->pop_size;i++)
  {
    for(pos=0; pos<pop->bit_count; pos++)
    {
      pop->ivd[i].crms[pos] = rand_between(0,1);
    }
  }
}
