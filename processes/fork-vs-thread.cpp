#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<cstdio>
#include<sys/wait.h>
#include<sys/resource.h>
#include<cstring>
#include<fcntl.h>

#define global_fork 10'000
#define global_thread 10'000
// mude para 1 para ver IDs
#define DEBUG 0 

int fork_id = 0;

void* pthreadFunction(void* pthnumber)
{
  long TID = (long)pthnumber;
  #if DEBUG
    std::cout << "Thread id: " << TID << '\n';
    TID++;
  #endif
  pthread_exit(NULL);
}

void print_usage(int who, const char* msg)
{
  struct rusage usage;
  getrusage(who, &usage);
  std::cout << msg << "Tempo: " << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << "s " << "\nRSS Max: " << usage.ru_maxrss << " KB\n\n";
}

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    const char* filepath = "cmd.txt";
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); exit(EXIT_FAILURE); } 
  
    const char* text = "\nComandos:\n\n Digite (./seu_comando thread) para logs thread.\n Digite (./seu_comando fork) para logs fork.\n Digite (./seu_comando tudo) para logs thread e fork.\n\nExcute novamente!\n\n";

    write(fd, text, strlen(text));

    pid_t pid_cmd = fork();
    if (pid_cmd < 0) { perror("pid_cmd"); exit(EXIT_FAILURE); }

    if (pid_cmd == 0)
    {
      execlp("cat", "cat", "cmd.txt", NULL);
      exit(EXIT_SUCCESS);
    }
    else 
    {
      waitpid(pid_cmd, NULL, 0);
      execlp("rm", "rm", "-rf", "cmd.txt", NULL);  
    }
  }

  // thread
  pthread_t threads[global_thread];
  int thread_create, thread_join;

  for (long i = 0; i < global_thread; i++)
  {
    thread_create = pthread_create(&threads[i], NULL, &pthreadFunction, (void*)i);
    if (thread_create < 0) { perror("thread_create"); exit(EXIT_FAILURE); }
  }

  for (long i = 0; i < global_thread; i++)
  {
    thread_join = pthread_join(threads[i], NULL);
    if (thread_join < 0) { perror("thread_join"); exit(EXIT_FAILURE); }
  }

  if (argc > 1) 
  {
    if (strcmp(argv[1], "thread") == 0)
    {
      std::cout << global_thread << " threads foram finalizados." << '\n';
      print_usage(RUSAGE_SELF, "\nthread logs: \n");
    }
  }

  // fork
  for (long i = 0; i < global_fork; i++)
  {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(EXIT_FAILURE); }
    if (pid == 0) { exit(EXIT_SUCCESS); }
    #if DEBUG
      std::cout << "Fork ID: " << fork_id << '\n';
      fork_id++;
    #endif
  }
  while(wait(NULL) > 0);

  if (argc > 1)
  {
    if (strcmp(argv[1], "fork") == 0)
    { 
      std::cout << global_fork << " forks foram finalizados." << '\n';
      print_usage(RUSAGE_CHILDREN, "\nFork logs: \n");
    }
    
    if (strcmp(argv[1], "tudo") == 0)
    {
      std::cout << global_thread << " threads foram finalizados." << '\n';
      print_usage(RUSAGE_SELF, "\nthread logs: \n");

      std::cout << global_fork << " forks foram finalizados." << '\n';
      print_usage(RUSAGE_CHILDREN, "\nFork logs: \n");
    }
  }
  return EXIT_SUCCESS;
}
****
