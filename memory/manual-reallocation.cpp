#include<iostream>

int main()
{
  int* array_antigo = new int[2];

  array_antigo[0] = 10;
  array_antigo[1] = 20;

  int N = 4;
  int* array_novo = new int[N];

  array_novo[0] = array_antigo[0];
  array_novo[1] = array_antigo[1];
  array_novo[2] = 30;
  array_novo[3] = 40;

  delete[] array_antigo;

  for (int i = 0; i < N; i++)
  {
    std::cout << array_novo[i] << " ";
  }

  delete[] array_novo;

  return 0;
}
