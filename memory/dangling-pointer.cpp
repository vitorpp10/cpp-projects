#include<iostream>

int main()
{
  int N = 10;
  int* ptr = new int(N);
  delete ptr;

  *ptr = 99;

  return 0;
}


/* Terminal
  
[vitor@vitor ~]$ g++ -Wall -Wextra -Werror s.cpp -o a && valgrind ./a
==66625== Memcheck, a memory error detector
==66625== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==66625== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
==66625== Command: ./a
==66625== 
==66625== Invalid write of size 4
==66625==    at 0x400119B: main (in /home/vitor/a)
==66625==  Address 0x4e65080 is 0 bytes inside a block of size 4 free'd
==66625==    at 0x484F8DD: operator delete(void*, unsigned long) (vg_replace_malloc.c:1181)
==66625==    by 0x4001196: main (in /home/vitor/a)
==66625==  Block was alloc'd at
==66625==    at 0x484BF93: operator new(unsigned long) (vg_replace_malloc.c:487)
==66625==    by 0x4001161: main (in /home/vitor/a)
==66625== 
==66625== 
==66625== HEAP SUMMARY:
==66625==     in use at exit: 0 bytes in 0 blocks
==66625==   total heap usage: 2 allocs, 2 frees, 73,732 bytes allocated
==66625== 
==66625== All heap blocks were freed -- no leaks are possible
==66625== 
==66625== For lists of detected and suppressed errors, rerun with: -s
==66625== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
[vitor@vitor ~]$ 
*/
