#include<iostream>

int main()
{
  int N = 50;
  int* ptr = new int(N);
  delete ptr;
  delete ptr;

  return 0;
}

/* Terminal


[vitor@vitor ~]$ g++ s.cpp -o a && ./a
free(): double free detected in tcache 2
Aborted                    (core dumped) ./a
[vitor@vitor ~]$ g++ -Wall -Wextra -Werror s.cpp -o a && ./a
free(): double free detected in tcache 2
Aborted                    (core dumped) ./a
[vitor@vitor ~]$ g++ -Wall -Wextra -Werror s.cpp -o a && valgrind ./a
==69506== Memcheck, a memory error detector
==69506== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==69506== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
==69506== Command: ./a
==69506== 
==69506== Invalid free() / delete / delete[] / realloc()
==69506==    at 0x484F8DD: operator delete(void*, unsigned long) (vg_replace_malloc.c:1181)
==69506==    by 0x40011AC: main (in /home/vitor/a)
==69506==  Address 0x4e65080 is 0 bytes inside a block of size 4 free'd
==69506==    at 0x484F8DD: operator delete(void*, unsigned long) (vg_replace_malloc.c:1181)
==69506==    by 0x4001196: main (in /home/vitor/a)
==69506==  Block was alloc'd at
==69506==    at 0x484BF93: operator new(unsigned long) (vg_replace_malloc.c:487)
==69506==    by 0x4001161: main (in /home/vitor/a)
==69506== 
==69506== 
==69506== HEAP SUMMARY:
==69506==     in use at exit: 0 bytes in 0 blocks
==69506==   total heap usage: 2 allocs, 3 frees, 73,732 bytes allocated
==69506== 
==69506== All heap blocks were freed -- no leaks are possible
==69506== 
==69506== For lists of detected and suppressed errors, rerun with: -s
==69506== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/
