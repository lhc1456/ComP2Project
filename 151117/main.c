#include "GA.h"

main()
{
  int i, j;
  int pop_size = 10;//��ü ��
  int bit_count = 2;// ����ü ��Ʈ ��
  int data_count = 2;//����ü ������ ��

  int sum_x = 0, sum_y = 0, avg_x, avg_y;

  int x, y;
  int check = 0;//���� ��ü���� ���� �������� �ݺ����� ���������� ���� ��

  int board[15][15] = {0};

  population *pop = create_population(pop_size, bit_count, data_count);//��ü�� ����

  play_board(pop, board);

  free_population(pop);

  printf("���� �����...");getch();
}

