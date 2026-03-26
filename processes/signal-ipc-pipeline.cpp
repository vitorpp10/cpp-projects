#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
#include<string>

 void handlerSigterm(int signum)
{
   const char* text = "\n[CHILD] SIGTERM received! Shutting down gracefully...\n";
   ssize_t w = write(STDOUT_FILENO, text, strlen(text));
   if (w < 0) { perror("Error in write.\n"); exit(EXIT_FAILURE); }

   exit(EXIT_SUCCESS);
 }

int main()
{
  int fildes[2];
  if (pipe(fildes) < 0) { perror("Error in pipe.\n"); exit(EXIT_FAILURE); }

  pid_t pid = fork();
  if (pid < 0) { perror("Error in fork.\n"); exit(EXIT_FAILURE); }

  if (pid == 0)
  {
    close(fildes[1]);
    signal(SIGTERM, handlerSigterm);

    char buffer[58] = {0};

    while (true)
    {
      ssize_t r = read(fildes[0], buffer, sizeof(buffer));
      if (r < 0) { perror("Error in read.\n"); break; }

      std::cout << "Child read: " << buffer << '\n';
    }
  }
  else 
  {
    close(fildes[0]);

    for (int i = 0; i < 3; i++)
    {
      std::string msg = "Task: " + std::to_string(i) + "\n";

      ssize_t w = write(fildes[1], msg.c_str(), msg.size());
      if (w < 0) { perror("Error in write"); continue; }

      sleep(1);
    }

    kill(pid, SIGTERM);

    waitpid(pid, NULL, 0);

    std::cout << "Parent collected the zombie. System clean. Exiting...\n";
  }
  return EXIT_SUCCESS;
}


/* Terminal:

[vitor@vitor ~]$ g++ s.cpp -o a && ./a
Child read: Task: 0
Child read: Task: 1
Child read: Task: 2

[CHILD] SIGTERM received! Shutting down gracefully...
Parent collected the zombie. System clean. Exiting...
[vitor@vitor ~]$ 
*/
