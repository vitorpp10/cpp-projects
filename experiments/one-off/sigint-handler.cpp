#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<cstring>

void handlerSignal(int signum)
{
  const char* text = "\n[SYSTEM NUMBER] SIGINT caught! Cleaning up and exiting gracefully...\n";
  ssize_t w = write(STDOUT_FILENO, text, strlen(text));
  if (w < 0) { perror("Erro no write text.\n"); exit(EXIT_FAILURE); }

  exit(EXIT_SUCCESS);
}

int main()
{
  signal(SIGINT, handlerSignal);

  while (true) { std::cout << "Program is running...\n"; sleep(1); }

  return EXIT_SUCCESS;
}


/* Terminal:

[vitor@vitor ~]$ g++ s.cpp -o a && ./a
Program is running...
Program is running...
Program is running...
Program is running...
Program is running...
^C
[SYSTEM NUMBER] SIGINT caught! Cleaning up and exiting gracefully...
[vitor@vitor ~]$ 
*/
