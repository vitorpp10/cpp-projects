#include<iostream>
#include<unistd.h>
#include<chrono>
#include<sys/types.h>
#include<cstring>
using namespace std;

int main()
{
  int fildes1[2], fildes2[2];
  if ((pipe(fildes1) < 0) || (pipe(fildes2) < 0)) { exit(EXIT_FAILURE); } 
 
  pid_t pid = fork();
  if (pid < 0) { exit(EXIT_FAILURE); }

  if (pid == 0)
  {
    close(fildes1[1]);
    close(fildes2[0]);

    for (size_t i = 0; i <= 100'000; i++)
    {
      char receive;
      read(fildes1[0], &receive, 1);

      char send = 'A';
      write(fildes2[1], &send, sizeof(send));
    }
  }
  else
  { 
    auto start = chrono::high_resolution_clock::now(); 

    close(fildes1[0]);
    close(fildes2[1]);

    for (size_t i = 0; i <= 100'000; i++)
    {
      char send = 'A';
      write(fildes1[1], &send, sizeof(send));

      char receive;
      read(fildes2[0], &receive, sizeof(receive));
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start; 
    cout << "duration: " << elapsed.count() << endl;
  }

  close(fildes1[1]);
  close(fildes2[1]);

  return 0;
}
