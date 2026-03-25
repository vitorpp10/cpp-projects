#include<iostream>

int main()
{
  int N;
  std::cin >> N;

  int* array = new int[N];

  for (int i = 0; i < N; i++)
  {
    std::cin >> array[i];
  }

  int* ptr_esquerda = &array[0];
  int* ptr_direita = &array[N-1];

  while (ptr_esquerda < ptr_direita)
  {
    int temp = *ptr_esquerda;
    *ptr_esquerda = *ptr_direita;
    *ptr_direita = temp;

    ptr_esquerda++;
    ptr_direita--;
  }

  std::cout << '\n';
  for (int i = 0; i < N; i++)
  {
    std::cout << array[i] << '\n';
  }
  
  std::cout << std::endl;
  delete[] array;
  return 0;
}
