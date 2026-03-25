#include<iostream>

int main()
{
  int N = 100;
  int* array = new int[N];

  int* ptr42 = &array[42];
  *ptr42 = array[0];

  return 0;
}


/* Terminal:

[vitor@vitor ~]$ g++ -Wall -Wextra -Werror s.cpp -o a && valgrind ./a
==65226== Memcheck, a memory error detector
==65226== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==65226== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
==65226== Command: ./a
==65226== 
==65226== 
==65226== HEAP SUMMARY:
==65226==     in use at exit: 400 bytes in 1 blocks
==65226==   total heap usage: 2 allocs, 1 frees, 74,128 bytes allocated
==65226== 
==65226== LEAK SUMMARY:
==65226==    definitely lost: 400 bytes in 1 blocks
==65226==    indirectly lost: 0 bytes in 0 blocks
==65226==      possibly lost: 0 bytes in 0 blocks
==65226==    still reachable: 0 bytes in 0 blocks
==65226==         suppressed: 0 bytes in 0 blocks
==65226== Rerun with --leak-check=full to see details of leaked memory
==65226== 
==65226== For lists of detected and suppressed errors, rerun with: -s
==65226== ERROR SUM
*/ 
