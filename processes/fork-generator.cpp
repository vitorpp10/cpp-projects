#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
  int count = 5;
  int wstatus;
  int pai = getpid();
  std::cout << "PID dad: " << pai << std::endl << std::endl;

  for (int i = 0; i < 5; i++)
  {
     pid_t pid = fork();
    if(pid == 0)
    {
      sleep(1);
      exit(0);
    }
    else 
    {
      continue;
    }
  }
  

  while (count > 0)
  {
    std::cout << "dad works..." << std::endl;
    sleep(1);

    pid_t dead_pid = waitpid(-1, &wstatus, WNOHANG);
    if (dead_pid > 0)
    {
      std::cout << "someone die, PID: " << dead_pid << std::endl;
      count--;
      continue;
    } 
    else if (dead_pid == 0)
    {
      std::cout << "always process lives " << std::endl;
      continue;
    }
    else if (dead_pid < 0)
    {
      std::cout << "finished" << std::endl;
      break;
    }
  }
  return 0;
}
