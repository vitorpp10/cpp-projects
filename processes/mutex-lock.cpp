#include<iostream>
#include<pthread.h>
#include<cstdio>
#include<sys/resource.h>

#define number_threads 10

int global_count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

void* pthreadFunction(void* argp)
{
  (void)argp; 
  for (int i = 0; i < 1'000'000; i++)
  {
    pthread_mutex_lock(&count_mutex);
    global_count++;
    pthread_mutex_unlock(&count_mutex);
  }
  pthread_exit(NULL);
}

void print_usage(int who, const char* txt)
{
  struct rusage usage;
  getrusage(who, &usage);
  std::cout << txt << "Tempo: " << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << "s " << "RSS max: " << usage.ru_maxrss << "/kB\n\n";
}

int main()
{
  pthread_t threads[number_threads];
  int thread_create, thread_join;

  for (int i = 0; i < number_threads; i++)
  {
    thread_create = pthread_create(&threads[i], NULL, &pthreadFunction, NULL);
    if (thread_create < 0) { perror("thread_create"); exit(EXIT_FAILURE); }
  }

  for (int i = 0; i < number_threads; i++)
  {
    thread_join = pthread_join(threads[i], NULL);
    if (thread_join < 0) { perror("thread_join"); exit(EXIT_FAILURE); }
  }
  
  print_usage(RUSAGE_SELF, "Thread logs:\n");
  std::cout << "global_count: " << global_count << std::endl;
  return EXIT_SUCCESS;
}
