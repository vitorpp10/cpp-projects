#include<iostream>

void funcaoPerigosa(int* ponteiro)
{
  *ponteiro = 42;
}

int main()
{
  int* ptr = nullptr;

  std::cout << "Iniciando o sistema...\n";

  funcaoPerigosa(ptr);

  std::cout << "Sistema finalizado com sucesso\n";
  return 0;
}

/* Terminal

[vitor@vitor ~]$ g++ -g s.cpp -o a && gdb ./a
GNU gdb (GDB) 17.1
Copyright (C) 2025 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-pc-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./a...
(gdb) run
Starting program: /home/vitor/a 

This GDB supports auto-downloading debuginfo from the following URLs:
  <https://debuginfod.archlinux.org>
Enable debuginfod for this session? (y or [n]) y
Debuginfod has been enabled.
To make this setting permanent, add 'set debuginfod enabled on' to .gdbinit.
Downloading 3.68 M separate debug info for /usr/lib/libm.so.6
Downloading 731.15 K separate debug info for /usr/lib/libgcc_s.so.1             
[Thread debugging using libthread_db enabled]                                   
Using host libthread_db library "/usr/lib/libthread_db.so.1".
Iniciando o sistema...

Program received signal SIGSEGV, Segmentation fault.
0x0000555555555145 in funcaoPerigosa (ponteiro=0x0) at s.cpp:5
5	  *ponteiro = 42;
(gdb) bt
#0  0x0000555555555145 in funcaoPerigosa (ponteiro=0x0) at s.cpp:5
#1  0x0000555555555183 in main () at s.cpp:14
(gdb) 
*/
