#include<iostream>
#include<pthread.h>
#include<cstdio>

#define t 10

int global_counter = 0;

void* pthreadFunction(void* msg)
{
  const char* message = (char*)msg;
  std::cout << "Thread " << message  << std::endl;
  for (int i = 0; i < 1'000'000; i++)
  {
    global_counter++;
  }
  pthread_exit(NULL);
}

int main()
{
  const char* message = " iniciou";

  pthread_t threads[t];
  int thread_create, thread_join;
  
  for (int i = 0; i < 10; i++)
  {
    thread_create = pthread_create(&threads[i], NULL, &pthreadFunction, (void*)message);
    if (thread_create < 0) { perror("thread_create"); exit(EXIT_FAILURE); }
  }

  for (int i = 0; i < 10; i++)
  {
    thread_join = pthread_join(threads[i], NULL);
    if (thread_join < 0) { perror("thread_join"); exit(EXIT_FAILURE); }
  }

  std::cout << t << " threads finalizados.\n";
  std::cout << "Count: " << global_counter << std::endl;
  return EXIT_SUCCESS;
}
