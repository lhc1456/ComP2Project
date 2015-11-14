#ifndef GA_H
#define GA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef int bit;

/*¿¿¿*/
typedef bit chromosome;

/*¿¿*/
typedef struct
{
  chromosome *crms;
  double fitness;//¿¿¿
}individual;

/*¿¿¿*/
typedef struct
{
  individual *ivd;
  int pop_size,//¿¿ ¿
      bit_count,//¿¿¿¿ ¿¿ ¿
      data_count;//¿¿¿ ¿¿ ¿¿¿ ¿
}population;

/*¿¿¿ ¿¿ : ¿¿¿¿ ¿¿¿¿ ¿¿¿¿¿¿. make : 151030*/
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

/*¿¿¿¿ ¿¿¿¿ ¿¿¿¿¿. make : 151030*/
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

/*a¿ b¿¿¿ ¿¿ ¿¿ ¿¿¿¿¿. make : 151031*/
int min(int a, int b)
{
  return (a<b) ? a:b;
}

/*a¿ b¿¿¿ ¿¿¿¿ ¿ ¿¿¿ ¿¿¿¿ ¿¿¿¿¿. make : 151031*/
int rand_between(int a, int b)
{
  int delta, randnum;

  delta = abs(a-b)+1;
  randnum = rand()%delta;

  return (min(a,b)+randnum);
}

/*¿¿¿¿ ¿¿¿¿ ¿¿¿¿ ¿¿¿¿¿¿. make : 151031*/
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

/*¿¿¿¿ ¿¿¿ ¿¿ ¿¿ ¿¿¿¿¿. make: 151105*/
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

/*¿¿¿¿ : XOR¿¿¿¿ ¿¿ ¿¿¿¿ ¿¿. make : 151107*/
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

/*¿¿¿ ¿¿ : ¿¿¿ ¿¿¿¿ ¿¿¿¿. make : 151108*/
void fitness_func(population *pop, int x, int y)
{
  int i;
  double fit;

  for(i=0; i<pop->pop_size; i++)
  {
    fit = hypot(pop->ivd[i].crms[0] - x, pop->ivd[i].crms[1]);
    if(fit > 1 && fit < 1.5)
    {
      pop->ivd[i].fitness += 0.1;
    }
  }
}

/*¿¿¿¿¿ ¿¿¿¿ ¿¿¿¿ ¿¿ ¿¿¿. make : 151109*/
void play_board(population *pop, int (*board)[15])
{
  int i, j,
      x, y,
      check = 0,
      sum_x, sum_y, avg_x, avg_y;

  while(1)
  {
    sum_x = 0; sum_y = 0;
    if(check == 0 || check == 2)//0¿ 2¿ ¿¿¿¿¿ ¿¿¿ ¿¿ ¿¿¿¿¿¿.
    {
      rand_population(pop);//¿¿¿¿ ¿¿¿ ¿ ¿¿¿¿ ¿¿¿
    }

    //display_population(pop);//¿¿¿¿ ¿¿¿ ¿ ¿¿

    if(check == 0 || check == 1)
    {
      printf("-9999¿¿¿ ¿¿\n");
      printf("x : ");
      scanf("%d", &x);
      if(x == -9999)
      {
        printf("¿¿¿¿¿.\n");
        break;
      }
      if(x<0 || x>14)
      {
        printf("ERROR\n");
        check = 2;//¿¿¿ ¿¿¿ ¿¿ ¿¿ ¿¿¿¿ ¿¿¿¿.
        continue;
      }

      printf("y : ");
      scanf("%d", &y);
      if(y == -9999)
      {
        printf("¿¿¿¿¿.\n");
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
            check = 1;//¿¿¿ ¿¿ ¿ ¿¿ ¿¿¿¿¿ ¿¿ ¿¿¿¿¿ ¿¿¿ ¿¿¿¿ ¿¿¿¿.
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
      check = 1;//¿¿¿¿¿ ¿¿¿¿ ¿¿ ¿¿¿ ¿¿ ¿¿¿¿ ¿¿ ¿¿¿¿ ¿¿ ¿¿¿¿ ¿¿¿¿.
      continue;
    }

    printf("%d %d\n", avg_x, avg_y);

    board[avg_y][avg_x] = 'X';//¿¿ ¿¿¿¿¿ ¿¿¿ board¿ ¿¿ ¿¿ ¿¿¿.
    board[y][x] = 'O';//¿¿¿¿¿ ¿¿¿¿ ¿¿¿¿ ¿¿¿ X¿ O¿ ¿¿¿ ¿¿¿¿.

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

/*¿¿¿ ¿¿¿ ¿¿¿¿. make : 151111*/
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

/*¿ ¿¿ ¿¿¿¿ ¿¿¿¿ ¿¿¿ ¿¿¿ ¿¿¿¿ ¿¿¿.*/
void crossover(chromosome *old_c1, chromosome *old_c2, chromosome *new_c1, chromosome *new_c2, int bit_count)
{
  int i,
      pos;

//¿¿¿¿ ¿¿¿¿ ¿¿¿¿.
  for(i=0; i<bit_count; i++)
  {
    new_c1[i] = old_c2[i];
    new_c2[i] = old_c1[i];
  }
//¿¿¿ ¿¿¿ ¿¿¿¿.
  pos = rand_between(0, bit_count-1);
//¿¿ ¿¿¿ ¿¿¿¿ ¿¿¿¿.
  new_c1[pos] = old_c1[pos];
  new_c2[pos] = old_c2[pos];
}

/*¿ ¿¿¿ ¿¿ ¿¿ ¿¿¿¿¿ ¿¿¿¿ ¿¿¿¿.*/
void breed(individual *old_v1, individual *old_v2, individual *new_v1, individual *new_v2, int bit_count)
{
  //¿¿¿¿¿.
  crossover(old_v1->crms, old_v2->crms, new_v1->crms, new_v2->crms, bit_count);

  //¿¿¿¿¿ ¿¿¿.
  mutate(new_v1->crms, bit_count);
  mutate(new_v2->crms, bit_count);
}

#endif

